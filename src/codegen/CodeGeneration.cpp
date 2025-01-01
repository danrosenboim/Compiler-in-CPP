#include "CodeGeneration.h"

CodeGeneration::CodeGeneration(const std::string& outputPath) : outputFile(outputPath), labels(0)
{
	if(!outputFile.is_open())
	{
		throw CompilerException("Could not open output file", 0);
	}
}

void CodeGeneration::generate(std::unique_ptr<ProgramNode> head)
{
	emit(".text");

	// Static allocator
	emit(".globl malloc_ptr");
	emit(".data");
	emit("malloc_ptr: .quad heap_start");
	emit(".bss");
	emit(".lcomm heap_start, 1000000"); // 1MB heap

	emit(".text");
	for (const auto& func : head->getFunctions())
	{
		generateFunction(func);
	}

	emit(".globl main");
	emit("main:");
	emit("pushq %rbp");
	emit("movq %rsp, %rbp");

	for (const auto& stmt : head->getStatements())
	{
		generateStatement(stmt);
	}

	emit("movq %rbp, %rsp");
	emit("popq %rbp");
	emit("ret");
}

void CodeGeneration::emit(const std::string& data) 
{
	outputFile << data << std::endl;
}

std::string CodeGeneration::createLabel()
{
	return ".L" + std::to_string(++labels);
}

void CodeGeneration::generateFunction(std::shared_ptr<FunctionNode> func)
{

}

void CodeGeneration::generateStatement(std::shared_ptr<StatementNode> statement)
{
	switch (statement->getStatementType())
	{
	case StatementType::DECLARATION:

	default:
	}
}

void CodeGeneration::generateDeclaration(std::shared_ptr<DeclarationStatementNode> decl)
{
	if (decl->getInitializer())
	{
		std::string result = generateExpression(decl->getInitializer());
		//emit("movq " + result + ", " + std::to_string(getOffset(decl->getIdentifier())) + "(%rbp)");
		regTable.registerFree(result);
	}
}

std::string CodeGeneration::generateExpression(std::shared_ptr<ExpressionNode> expr)
{
    std::string reg = regTable.registerAllocate();

    switch (expr->getExpressionVariant()) {
    case ExpressionType::NUMBER: {
        auto numExpr = std::dynamic_pointer_cast<NumberExpr>(expr);
        emit("movq $" + std::to_string(numExpr->getValue()) + ", " + reg);
        break;
    }
    case ExpressionType::REAL: {
        auto realExpr = std::dynamic_pointer_cast<RealExpr>(expr);
        std::string temp = regTable.registerAllocate();
        emit("movq $" + std::to_string(*(uint64_t*)&realExpr->getValue()) + ", " + temp);
        emit("movq " + temp + ", " + reg);
        regTable.registerFree(temp);
        break;
    }
    case ExpressionType::BOOL: {
        auto boolExpr = std::dynamic_pointer_cast<BoolExpr>(expr);
        emit("movq $" + std::to_string(boolExpr->getValue() ? 1 : 0) + ", " + reg);
        break;
    }
    case ExpressionType::BINARY: {
        regTable.registerFree(reg);
        reg = generateBinaryExpr(std::dynamic_pointer_cast<BinaryExpr>(expr));
        break;
    }
    case ExpressionType::IDENTIFIER: {
        auto idExpr = std::dynamic_pointer_cast<IdentifierExpr>(expr);
        emit("movq " + idExpr->getName() + "(%rip), " + reg);
        break;
    }
    case ExpressionType::NOT: {
        auto notExpr = std::dynamic_pointer_cast<NotExpr>(expr);
        std::string operand = generateExpression(notExpr->getExpression());
        emit("movq " + operand + ", " + reg);
        emit("xorq $1, " + reg);
        regTable.registerFree(operand);
        break;
    }
    }

    if (expr->getNeedsConversion()) {
        convertType(reg, expr->getExpressionType(), expr->getTargetType());
    }

    return reg;
}

std::string CodeGeneration::generateBinaryExpr(std::shared_ptr<BinaryExpr> expr) {
    std::string left = generateExpression(expr->getLeft());
    std::string right = generateExpression(expr->getRight());
    std::string result = regTable.registerAllocate();

    emit("movq " + left + ", " + result);

    switch (expr->getType()) {
    case BinaryExprType::ADD:
        emit("addq " + right + ", " + result);
        break;
    case BinaryExprType::SUB:
        emit("subq " + right + ", " + result);
        break;
    case BinaryExprType::MUL:
        emit("imulq " + right + ", " + result);
        break;
    case BinaryExprType::DIV:
        emit("movq " + result + ", %rax");
        emit("cqto");  // Sign extend RAX into RDX:RAX
        emit("idivq " + right);
        emit("movq %rax, " + result);
        break;
    case BinaryExprType::EQUAL_EQUAL:
        emit("cmpq " + right + ", " + result);
        emit("sete %al");
        emit("movzbq %al, " + result);
        break;
    case BinaryExprType::NOT_EQUAL:
        emit("cmpq " + right + ", " + result);
        emit("setne %al");
        emit("movzbq %al, " + result);
        break;
    case BinaryExprType::LESS:
        emit("cmpq " + right + ", " + result);
        emit("setl %al");
        emit("movzbq %al, " + result);
        break;
    case BinaryExprType::LESS_EQUAL:
        emit("cmpq " + right + ", " + result);
        emit("setle %al");
        emit("movzbq %al, " + result);
        break;
    case BinaryExprType::GREATER:
        emit("cmpq " + right + ", " + result);
        emit("setg %al");
        emit("movzbq %al, " + result);
        break;
    case BinaryExprType::GREATER_EQUAL:
        emit("cmpq " + right + ", " + result);
        emit("setge %al");
        emit("movzbq %al, " + result);
        break;
    }

    regTable.registerFree(left);
    regTable.registerFree(right);
    return result;
}

void CodeGeneration::convertType(std::string& reg, TypeKind from, TypeKind to) {
    if (from == to) return;

    std::string temp = regTable.registerAllocate();

    switch (to) {
    case TypeKind::NUM:
        if (from == TypeKind::REAL) {
            emit("cvttsd2siq " + reg + ", " + temp);
            emit("movq " + temp + ", " + reg);
        }
        break;
    case TypeKind::REAL:
        if (from == TypeKind::NUM) {
            emit("cvtsi2sdq " + reg + ", " + temp);
            emit("movq " + temp + ", " + reg);
        }
        break;
    }

    regTable.registerFree(temp);
}