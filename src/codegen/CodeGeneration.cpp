#include "CodeGeneration.h"

CodeGeneration::CodeGeneration(const std::string& outputPath) : outputFile(outputPath), labels(0)
{
	if(!outputFile.is_open())
	{
		throw CompilerException("Could not open output file", 0);
	}

	emit(".file \"" + outputPath.substr(outputPath.find('/') + 1, outputPath.size() - outputPath.find('/') + 1) + "\"");
	emit(".text");
}

void CodeGeneration::generate(std::unique_ptr<ProgramNode> head)
{

	emit(".bss");
	for (const auto& decl : head->getDeclarations())
	{
		generateGlobal(decl);
	}

	emit(".text");
	for (const auto& func : head->getFunctions())
	{
		//generateFunction(func);
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

uint32_t CodeGeneration::floatToIEEE(float value)
{
    // Using a union to access the float's bits directly
    union {
        float f;
        uint32_t i;
    } converter;

    // Store the float in the union
    converter.f = value;

    // Return the value interpreted as an int
    return converter.i;
}

void CodeGeneration::generateGlobal(std::shared_ptr<Symbol> symbol)
{
	emit(".global " + symbol->varName);
	emit(".bss");
	
	// Generate different variables, depending on the declaration type
	switch (symbol->varType)
	{
	case TypeKind::NUM:
	case TypeKind::REAL:
		emit(".align 4");
		emit(".type " + symbol->varName + ", @object");
		emit(".size " + symbol->varName + ", 4");
		emit(symbol->varName + ":");
		emit(".zero 4");
		break;
	case TypeKind::BOOL:
		emit(".type " + symbol->varName + ", @object");
		emit(".size " + symbol->varName + ", 1");
		emit(symbol->varName + ":");
		emit(".zero 1");
		break;
	default:
		std::cout << "Not implemented yet" << std::endl;
	}
}

//void CodeGeneration::generateFunction(std::shared_ptr<FunctionNode> func)
//{
//
//}

void CodeGeneration::generateStatement(std::shared_ptr<StatementNode> statement)
{
	switch (statement->getStatementType())
	{
	case StatementType::DECLARATION:
		generateDeclaration(std::dynamic_pointer_cast<DeclarationStatementNode>(statement));

	default:
	}
}

void CodeGeneration::generateDeclaration(std::shared_ptr<DeclarationStatementNode> decl)
{
	if (decl->getInitializer())
	{
		std::string resultReg = generateExpression(decl->getInitializer());
		//emit("movq " + resultReg + ", " + std::to_string(getOffset(decl->getIdentifier())) + "(%rbp)");
		regTable.registerFree(resultReg);
	}
}

std::string CodeGeneration::generateExpression(std::shared_ptr<ExpressionNode> expr)
{
    std::string reg = "";
    std::string reg2 = "";
    switch (expr->getExpressionVariant())
    {
    case ExpressionType::NUMBER:
        reg = regTable.registerAllocate();
        emit("movl $" + std::to_string(std::dynamic_pointer_cast<NumberExpr>(expr)->getValue()) + ", " + reg);
        break;

    case ExpressionType::REAL:
        std::cout << "Not Implemented yet" << std::endl;
        // Allocating a GP register for the IEEE 754 Representation
        reg2 = regTable.registerAllocate();

        // Allocating the final result register
        reg = regTable.floatRegisterAllocate();

        emit("movl $" + std::to_string(floatToIEEE(std::dynamic_pointer_cast<RealExpr>(expr)->getValue())) + ", " + reg2);
        emit("movl " + reg2 + ", " + reg);

        // We can free the temp register we used
        regTable.registerFree(reg2);

        break;

    case ExpressionType::BOOL:
        reg = regTable.registerAllocate();
        emit("movb $" + std::to_string(std::dynamic_pointer_cast<BoolExpr>(expr)->getValue() ? 1 : 0) + ", " + reg);
        break;

    case ExpressionType::STRING:
        std::cout << "Not Implemented yet" << std::endl;
        break;

    case ExpressionType::BINARY:
        reg = generateBinaryExpr(std::dynamic_pointer_cast<BinaryExpr>(expr));
        break;

    case ExpressionType::IDENTIFIER:
        reg = regTable.registerAllocate();
        emit("movl " + std::dynamic_pointer_cast<IdentifierExpr>(expr)->getName() + "(%rip), " + reg);
        break;

    case ExpressionType::NOT:
        reg = generateExpression(std::dynamic_pointer_cast<NotExpr>(expr)->getExpression());
        emit("xorb $1, " + reg + "b"); // Toggle the boolean value
        return reg;

    case ExpressionType::FUNC_CALL:
        std::cout << "Not implemented yet" << std::endl;
        //auto funcExpr = std::dynamic_pointer_cast<FunctionCallExpr>(expr);
        //// Save registers before function call
        //emit("pushq %rax");
        //emit("pushq %rcx");
        //emit("pushq %rdx");
        //
        //// Generate code for arguments in reverse order
        //auto args = funcExpr->getArguments();
        //for (auto it = args.rbegin(); it != args.rend(); ++it) {
        //    std::string argReg = generateExpression(*it);
        //    emit("pushq " + argReg);
        //    regTable.registerFree(argReg);
        //}
        //
        //// Call function
        //emit("call " + funcExpr->getName());
        //
        //// Clean up stack
        //if (!args.empty()) {
        //    emit("addq $" + std::to_string(args.size() * 8) + ", %rsp");
        //}
        //
        //// Restore registers
        //emit("popq %rdx");
        //emit("popq %rcx");
        //emit("popq %rax");
        //
        //// Move result to a new register
        //std::string resultReg = regTable.registerAllocate();
        //emit("movl %eax, " + resultReg);
        //return resultReg;
        break;
    default:
        throw CompilerException("Unsupported expression type in code generation", expr->getLineNumber());
    }

    // Convert item if needed
    if (expr->getNeedsConversion())
    {
        TypeKind from = expr->getExpressionType();
        TypeKind to = expr->getTargetType();
        std::string newReg;

        // Convert to bool
        if (to == TypeKind::BOOL)
        {
            if (from == TypeKind::NUM)
            {
                // Convert num to bool
                emit("cmpl $0, " + reg);
                emit("setne " + reg + "b");
                emit("movzbq " + reg + "b, " + reg);
            }
            else if (from == TypeKind::REAL)
            {
                std::string zeroReg = regTable.floatRegisterAllocate();
                emit("xorps " + zeroReg + ", " + zeroReg); // Set Register to 0
                emit("ucomiss " + zeroReg + ", " + reg); // Unordered compare float with 0
                emit("setne " + reg + "b"); // Set to 1 if not equal
                emit("movzbq " + reg + "b, " + reg); // Zero-extend to full register
                regTable.registerFree(zeroReg);
            }
            return reg;
        }

        // Convert float to num
        if (to == TypeKind::NUM)
        {
            if (from == TypeKind::REAL)
            {
                newReg = regTable.registerAllocate();
                emit("cvttss2si " + reg + ", " + newReg); // cvt(convert) t(truncate) ss(single precision) si(signed int)
                regTable.registerFree(reg);
                reg = newReg;
            }
            return reg;
        }

        // Convert to float
        if ((from == TypeKind::BOOL || from == TypeKind::NUM) && to == TypeKind::REAL)
        {
            newReg = regTable.floatRegisterAllocate();
            emit("cvtsi2ss " + reg + ", " + newReg);  // Convert integer to float
            regTable.registerFree(reg);
            reg = newReg;
            return reg;
        }
    }

    return reg;
}

std::string CodeGeneration::generateBinaryExpr(std::shared_ptr<BinaryExpr> binExpr)
{
    std::string reg = generateExpression(binExpr->getLeft());
    std::string rightReg = generateExpression(binExpr->getRight());
    
    // Both sides of the 
    switch (binExpr->getTargetType())
    {
    // TODO ADD STRING
    case TypeKind::BOOL:
    case TypeKind::NUM:
    {
        switch (binExpr->getType())
        {
        case BinaryExprType::ADD:
            emit("addl " + rightReg + ", " + reg);
            break;

        case BinaryExprType::SUB:
            emit("subl " + rightReg + ", " + reg);
            break;

        case BinaryExprType::MUL:
            emit("imull " + rightReg + ", " + reg);
            break;

        case BinaryExprType::DIV:
            emit("pushq %rdx");
            emit("movl " + reg + ", %eax");
            // Convert long to double long
            emit("cltd");
            emit("idivl " + rightReg);
            emit("movl %eax, " + reg);
            emit("popq %rdx"); // Retrieve RDX
            break;

        case BinaryExprType::GREATER:
            emit("cmpl " + rightReg + ", " + reg);
            emit("setg " + reg + "b");
            emit("movzbq " + reg + "b, " + reg);
            break;

        case BinaryExprType::GREATER_EQUAL:
            emit("cmpl " + rightReg + ", " + reg);
            emit("setge " + reg + "b");
            emit("movzbq " + reg + "b, " + reg);
            break;

        case BinaryExprType::LESS:
            emit("cmpl " + rightReg + ", " + reg);
            emit("setl " + reg + "b");
            emit("movzbq " + reg + "b, " + reg);
            break;

        case BinaryExprType::LESS_EQUAL:
            emit("cmpl " + rightReg + ", " + reg);
            emit("setle " + reg + "b");
            emit("movzbq " + reg + "b, " + reg);
            break;

        case BinaryExprType::EQUAL_EQUAL:
            emit("cmpl " + rightReg + ", " + reg);
            emit("sete " + reg + "b");
            emit("movzbq " + reg + "b, " + reg);
            break;

        case BinaryExprType::NOT_EQUAL:
            emit("cmpl " + rightReg + ", " + reg);
            emit("setne " + reg + "b");
            emit("movzbq " + reg + "b, " + reg);
            break;
        }
        break;
    }
    // Different operations for floats
    case TypeKind::REAL:
    {
        switch (binExpr->getType())
        {
        case BinaryExprType::ADD:
            emit("addss " + rightReg + ", " + reg);
            break;
        case BinaryExprType::SUB:
            emit("subss " + rightReg + ", " + reg);
            break;
        case BinaryExprType::MUL:
            emit("mulss " + rightReg + ", " + reg);
            break;
        case BinaryExprType::DIV:
            emit("divss " + rightReg + ", " + reg);
            break;
        case BinaryExprType::GREATER:
            emit("ucomiss " + rightReg + ", " + reg);
            emit("seta " + reg + "b");
            emit("movzbq " + reg + "b, " + reg);
            break;
        case BinaryExprType::GREATER_EQUAL:
            emit("ucomiss " + rightReg + ", " + reg);
            emit("setae " + reg + "b");
            emit("movzbq " + reg + "b, " + reg);
            break;
        case BinaryExprType::LESS:
            emit("ucomiss " + reg + ", " + rightReg);
            emit("seta " + reg + "b");
            emit("movzbq " + reg + "b, " + reg);
            break;
        case BinaryExprType::LESS_EQUAL:
            emit("ucomiss " + reg + ", " + rightReg);
            emit("setae " + reg + "b");
            emit("movzbq " + reg + "b, " + reg);
            break;
        case BinaryExprType::EQUAL_EQUAL:
            emit("ucomiss " + rightReg + ", " + reg);
            emit("sete " + reg + "b");
            emit("movzbq " + reg + "b, " + reg);
            break;
        case BinaryExprType::NOT_EQUAL:
            emit("ucomiss " + rightReg + ", " + reg);
            emit("setne " + reg + "b");
            emit("movzbq " + reg + "b, " + reg);
            break;
        }
        break;
    }
    }

    regTable.registerFree(rightReg);
    return reg;
}
