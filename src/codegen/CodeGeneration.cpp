#include "CodeGeneration.h"

CodeGeneration::CodeGeneration(const std::string& inputPath, const std::string& outputPath) : outputFile(outputPath), labels(0), regTable(), scopeManager()
{
	if(!outputFile.is_open())
	{
        throw CodeGenCantOutputOpenOutputFile(outputPath);
	}

	emit(".file \"" + inputPath + "\"");
	emit(".text");
}

void CodeGeneration::generate(std::unique_ptr<ProgramNode> head)
{
    // Generating the bss section for global variables and initializing them in main
	emit(".bss");
	for (const auto& decl : head->getDeclarations())
	{
		generateGlobal(decl);
	}

    // Generating all the functions
	emit(".text");
	for (const auto& func : head->getFunctions())
	{
		generateFunction(func);
	}

    // Generating main function
	emit(".globl main");
	emit("main:");
	emit("pushq %rbp");
	emit("movq %rsp, %rbp");

	for (const auto& stmt : head->getStatements())
	{
		generateStatement(stmt);
	}

    emit("movq $0, %rax"); // Return 0 by default
	emit("movq %rbp, %rsp");
	emit("popq %rbp");
	emit("ret");

    emit(".rodata");
    emit(".align 4");
    emit(".float_1000:");
    emit(".long 0x447A0000");  // IEEE 754 representation of 1000

    // Generate the final .rodata section
    generateStringLiterals();
}

void CodeGeneration::emit(const std::string& data) 
{
	outputFile << data << std::endl;
}

std::string CodeGeneration::addStringLiteral(const std::string& str)
{
    // Check if we already have this string
    if (stringLiterals.find(str) != stringLiterals.end())
    {
        return stringLiterals[str];
    }

    // Create new label for this string
    std::string label = ".LC" + std::to_string(stringLiterals.size());
    stringLiterals[str] = label;
    return label;
}

void CodeGeneration::generateStringLiterals()
{
    if (stringLiterals.empty()) return;

    for (const auto& [str, label] : stringLiterals)
    {
        emit(label + ":");
        emit(".string \"" + str + "\"");
        emit(".align 8");
    }
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
    case TypeKind::TEXT:
        emit(".align 8");
        emit(".type " + symbol->varName + ", @object");
        emit(".size " + symbol->varName + ", 8");
        emit(symbol->varName + ":");
        emit(".quad 0");
        break;
	default:
        break;
	}
}

void CodeGeneration::generateFunction(std::shared_ptr<FunctionNode> func)
{
    // Generate function label
    emit(".globl " + func->getName());
    emit(func->getName() + ":");

    // Stack frame
    emit("pushq %rbp");
    emit("movq %rsp, %rbp");

    // Allocating stack space
    int stackSpace = ((func->getBody()->getDeclarations().size() * 8 + func->getParameters().size() * 8 + 15) / 16) * 16;
    if (stackSpace > 0)
    {
        emit("subq $" + std::to_string(stackSpace) + ", %rsp");
    }

    emit("pushq %rbx");
    emit("pushq %r12");
    emit("pushq %r13");
    emit("pushq %r14");
    emit("pushq %r15");

    // Enter new scope
    scopeManager.enterScope(stackSpace);

    const auto& params = func->getParameters();
    std::vector<std::string> intRegs = { "%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9" };
    std::vector<std::string> xmmRegs = { "%xmm0", "%xmm1", "%xmm2", "%xmm3", "%xmm4", "%xmm5", "%xmm6", "%xmm7" };

    int intRegCount = 0;
    int xmmRegCount = 0;

    // Registering all parameters with scope manager
    for (const auto& param : params)
    {
        scopeManager.addVariable(param->getIdentifier());
    }

    // Keep track of parameters that go on stack
    int stackParamsCount = 0;

    // Move parameters to their stack locations
    for (size_t i = 0; i < params.size(); i++)
    {
        int offset = scopeManager.addVariable(params[i]->getIdentifier());

        if (params[i]->getType() == TypeKind::REAL)
        {
            // Filling up 8 xmm registers
            if (xmmRegCount < 8)
            {
                emit("movss " + xmmRegs[xmmRegCount++] + ", " + std::to_string(offset) + "(%rbp)");
            }
            else
            {
                // This parameter goes on stack
                int stackParamOffset = 16 + (stackParamsCount++ * 8);
                emit("movss " + std::to_string(stackParamOffset) + "(%rbp), %xmm0");
                emit("movss %xmm0, " + std::to_string(offset) + "(%rbp)");
            }
            continue;
        }
        // Filling up 6 general purpose registers
        if (intRegCount < 6)
        {
            emit("movq " + intRegs[intRegCount++] + ", " + std::to_string(offset) + "(%rbp)");
        }
        else
        {
            // This parameter goes on stack
            int stackParamOffset = 16 + (stackParamsCount++ * 8);
            emit("movq " + std::to_string(stackParamOffset) + "(%rbp), %rax");
            emit("movq %rax, " + std::to_string(offset) + "(%rbp)");
        }
    }

    // Generate the code block
    generateBlock(func->getBody(), false);

    // Function ending label for returns
    std::string endingLabel = createLabel();
    emit(endingLabel + ":");

    // Restore callee-saved registers
    emit("popq %r15");
    emit("popq %r14");
    emit("popq %r13");
    emit("popq %r12");
    emit("popq %rbx");

    // Function ending
    emit("movq %rbp, %rsp");
    emit("popq %rbp");
    emit("ret");

    // Store ending label for use in return statements
    functionEndings[func->getName()] = endingLabel;
}

void CodeGeneration::generateBlock(std::shared_ptr<BlockNode> block, bool enterScope)
{
    int allocationNeeded = 0;

    if (enterScope)
    {
        // Block frame
        emit("pushq %rbp");
        emit("movq %rsp, %rbp");

        allocationNeeded = ((block->getDeclarations().size() * 8 + 15) / 16) * 16; // Round to 16
        // Create new scope if the user requests
        if (allocationNeeded > 0)
        {
            emit("subq $" + std::to_string(allocationNeeded) + ", %rsp");
        }
        scopeManager.enterScope(allocationNeeded);
    }

    // Generate all the statements in the block
    for (const auto& elem : block->getStatements())
    {
        generateStatement(elem);
    }

    if (enterScope)
    {
        // Exit the scope
        scopeManager.exitScope();
        emit("movq %rbp, %rsp");
        emit("popq %rbp");
    }
}

void CodeGeneration::generateStatement(std::shared_ptr<StatementNode> statement)
{
    // Generate the correct statement type
	switch (statement->getStatementType())
	{
    case StatementType::ASSIGNMENT:
        generateAssignment(std::dynamic_pointer_cast<AssignmentStatementNode>(statement));
        break;
	case StatementType::DECLARATION:
		generateDeclaration(std::dynamic_pointer_cast<DeclarationStatementNode>(statement));
        break;
    case StatementType::FOR:
        generateForStatement(std::dynamic_pointer_cast<ForStatementNode>(statement));
        break;
    case StatementType::IF:
        generateIfStatement(std::dynamic_pointer_cast<IfStatementNode>(statement));
        break;
    case StatementType::IN:
    case StatementType::OUT:
    case StatementType::RETURN:
        generateReturn(std::dynamic_pointer_cast<ReturnStatementNode>(statement));
        break;
    case StatementType::ERROR:
	default:
        break;
	}
}

void CodeGeneration::generateAssignment(std::shared_ptr<AssignmentStatementNode> assignment)
{
    std::string resultReg = generateExpression(assignment->getExpression());
    std::string variableReg = "";
    std::string tempReg = "";

    // Get correct offset
    auto [levelDiff, offset] = scopeManager.getVariableOffset(assignment->getIdentifier());

    // Check if we're in global scope
    if (levelDiff == -1)
    {
        variableReg = assignment->getIdentifier() + "(%rip)";
    }
    else
    {
        std::string tempReg = "%rbp";

        // Getting the variable offset from different scopes
        if (levelDiff > 0)
        {
            tempReg = regTable.registerAllocate();
            emit("movq %rbp, " + tempReg);

            // Follow static chain up to the correct scope
            for (int i = 0; i < levelDiff; i++)
            {
                emit("movq (" + tempReg + "), " + tempReg);
            }
        }

        variableReg = std::to_string(offset) + "(" + tempReg + ")";
    }

    // Global variable initialization
    switch (assignment->getExpression()->getExpressionType())
    {
    case TypeKind::NUM:
        emit("movl " + resultReg + ", " + variableReg);
        break;
    case TypeKind::REAL:
        emit("movss " + resultReg + ", " + variableReg);
        break;
    case TypeKind::BOOL:
        emit("movb " + resultReg + "b, " + variableReg);
        break;
    case TypeKind::TEXT:
        emit("movq " + resultReg + ", " + variableReg);
        break;
    }

    regTable.registerFree(resultReg);
    if (tempReg != "")
    {
        regTable.registerFree(tempReg);
    }
}

void CodeGeneration::generateDeclaration(std::shared_ptr<DeclarationStatementNode> decl)
{
    scopeManager.addVariable(decl->getIdentifier());
    // Already allocated all space needed when the block initialized
    if (!decl->getInitializer())
    {
        return;
    }

    std::string resultReg = generateExpression(decl->getInitializer());
    std::string variableReg = "";
    std::string tempReg = "";
    
    // Get correct offset
    auto [levelDiff, offset] = scopeManager.getVariableOffset(decl->getIdentifier());

    // Check if we're in global scope
    if (levelDiff == -1)
    {
        variableReg = decl->getIdentifier() + "(%rip)";
    }
    else
    {
        std::string tempReg = "%rbp";
            
        // Getting the variable offset from different scopes
        if (levelDiff > 0)
        {
            tempReg = regTable.registerAllocate();
            emit("movq %rbp, " + tempReg);

            // Follow static chain up to the correct scope
            for (int i = 0; i < levelDiff; i++)
            {
                emit("movq (" + tempReg + "), " + tempReg);
            }
        }

        variableReg = std::to_string(offset) + "(" + tempReg + ")";
    }

    // Global variable initialization
    switch (decl->getType())
    {
    case TypeKind::NUM:
        emit("movl " + resultReg + ", " + variableReg);
        break;
    case TypeKind::REAL:
        emit("movss " + resultReg + ", " + variableReg);
        break;
    case TypeKind::BOOL:
        emit("movb " + resultReg + "b, " + variableReg);
        break;
    case TypeKind::TEXT:
        emit("movq " + resultReg + ", " + variableReg);
        break;
    }
    
    regTable.registerFree(resultReg);
    if (tempReg != "")
    {
        regTable.registerFree(tempReg);
    }
}

void CodeGeneration::generateForStatement(std::shared_ptr<ForStatementNode> forNode)
{
    // Stack frame
    emit("pushq %rbp");
    emit("movq %rsp, %rbp");

    // Allocating space for the loop variable and any variables in the body
    int allocationNeeded = ((forNode->getBody()->getDeclarations().size() * 8 + 8 + 15) / 16) * 16; // Round to 16
    emit("subq $" + std::to_string(allocationNeeded) + ", %rsp");
    scopeManager.enterScope(allocationNeeded);

    // Add the loop variable to scope
    scopeManager.addVariable(forNode->getVariableName());

    // Get initialization expression into a register and store it
    std::string initReg = generateExpression(forNode->getInitExpr());
    auto [levelDiff, offset] = scopeManager.getVariableOffset(forNode->getVariableName()); // Level diff is equal to 0 because were still in the same scope
    emit("movl " + initReg + ", " + std::to_string(offset) + "(%rbp)");
    regTable.registerFree(initReg);

    // Create loop and end label
    std::string loopLabel = createLabel();
    std::string doneLabel = createLabel();

    // Loop start
    emit(loopLabel + ":");

    // Generate and check condition
    std::string condReg = generateExpression(forNode->getCondition());
    emit("cmpl $0, " + condReg);
    regTable.registerFree(condReg);
    emit("je " + doneLabel);

    // Generate loop body
    generateBlock(forNode->getBody(), false); // false because we already created a scope

    // Increment loop variable
    emit("incl " + std::to_string(offset) + "(%rbp)");

    // Jump back to condition check
    emit("jmp " + loopLabel);

    // Loop end
    emit(doneLabel + ":");

    scopeManager.exitScope();
    emit("movq %rbp, %rsp");
    emit("popq %rbp");
}

void CodeGeneration::generateIfStatement(std::shared_ptr<IfStatementNode> ifNode)
{
    // Setting up labels
    bool elseLabelBool = ifNode->getElseBlock() != nullptr;
    std::string elseLabel = "";
    if (elseLabelBool)
    {
        elseLabel = createLabel();
    }

    std::string doneLabel = createLabel();

    // Generate condition
    std::string resultReg = generateExpression(ifNode->getCondition());

    // Check condition
    emit("cmp $0, " + resultReg);
    regTable.registerFree(resultReg);
    if (elseLabelBool)
    {
        emit("je " + elseLabel);
    }
    else
    {
        emit("je " + doneLabel);
    }
    generateBlock(ifNode->getBody(), true);
    emit("jmp " + doneLabel);

    // Create else if it exists;
    if (elseLabelBool)
    {
        emit(elseLabel + ":");
        generateBlock(ifNode->getElseBlock(), true);
    }

    emit(doneLabel + ":");
}

void CodeGeneration::generateOutStatement(std::shared_ptr<OutStatementNode> outNode)
{
    // Generate the expression to be printed
    std::string resultReg = generateExpression(outNode->getExpression());

    switch (outNode->getExpression()->getExpressionType())
    {
    case TypeKind::NUM:
    {
        generateNumberOut(resultReg);
        generateNewLineOut();
        break;
    }
    case TypeKind::BOOL:
    {
        // Add string literals for "true" and "false"
        std::string trueLabel = addStringLiteral("true\n");
        std::string falseLabel = addStringLiteral("false\n");

        std::string printFalse = createLabel();
        std::string endPrint = createLabel();

        // Test the boolean value
        emit("testb " + resultReg + "b, " + resultReg + "b");
        emit("jz " + printFalse);

        // Print "true"
        emit("movq $1, %rax");      // sys_write
        emit("movq $1, %rdi");      // stdout
        emit("leaq " + trueLabel + "(%rip), %rsi");
        emit("movq $5, %rdx");      // length = 5 ("true\n")
        emit("syscall");
        emit("jmp " + endPrint);

        // Print "false"
        emit(printFalse + ":");
        emit("movq $1, %rax");      // sys_write
        emit("movq $1, %rdi");      // stdout
        emit("leaq " + falseLabel + "(%rip), %rsi");
        emit("movq $6, %rdx");      // length = 6 ("false\n")
        emit("syscall");

        emit(endPrint + ":");
        break;
    }
    case TypeKind::TEXT:
    {
        // For text, we need to print the string and a newline
        // First print the string
        emit("movq $1, %rax");      // sys_write
        emit("movq $1, %rdi");      // stdout
        emit("movq " + resultReg + ", %rsi");  // string pointer

        // Calculate string length (find null terminator)
        emit("xorq %rdx, %rdx");    // Clear length counter
        std::string lengthLoop = createLabel();
        emit(lengthLoop + ":");
        emit("cmpb $0, (%rsi, %rdx)");  // Check for null terminator
        emit("je " + createLabel());     // Exit if found
        emit("incq %rdx");              // Increment length
        emit("jmp " + lengthLoop);

        // Print the string
        emit("syscall");

        // Print newline
        emit("movq $1, %rax");      // sys_write
        emit("movq $1, %rdi");      // stdout
        emit("pushq $10");          // Push newline character
        emit("movq %rsp, %rsi");    // Point to newline
        emit("movq $1, %rdx");      // length = 1
        emit("syscall");
        emit("addq $8, %rsp");      // Clean up stack
        break;
    }
    case TypeKind::REAL:
    {
        generateFloatOut(resultReg);
        generateNewLineOut();
        break;
    }
    }

    regTable.registerFree(resultReg);
}

void CodeGeneration::generateReturn(std::shared_ptr<ReturnStatementNode> returnStmt)
{
    // Generate the return expression
    std::string resultReg = generateExpression(returnStmt->getExpression());

    // Move result to return register based on type
    switch (returnStmt->getExpression()->getExpressionType())
    {
    case TypeKind::NUM:
    case TypeKind::BOOL:
        emit("movl " + resultReg + ", %eax");
        break;
    case TypeKind::REAL:
        emit("movss " + resultReg + ", %xmm0");
        break;
    case TypeKind::TEXT:
        emit("movq " + resultReg + ", %rax");  // Move pointer to return register
        break;
    }

    // Free the register
    regTable.registerFree(resultReg);

    // Jump to function epilogue
    emit("jmp " + functionEndings[returnStmt->getFunctionName()]);
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
    {
        std::string strValue = std::dynamic_pointer_cast<StringExpr>(expr)->getValue();
        std::string strLabel = addStringLiteral(strValue);
        reg = regTable.registerAllocate();
        emit("leaq " + strLabel + "(%rip), " + reg);
        break;
    }

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
        break;

    case ExpressionType::FUNC_CALL:
        reg = generateFunctionCall(std::dynamic_pointer_cast<FunctionCallExpr>(expr));
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
    switch (binExpr->getExpressionType())
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
    case TypeKind::TEXT:
    {
        // Only 2 operations for string
        switch (binExpr->getType())
        {
        case BinaryExprType::EQUAL_EQUAL:
            emit("cmpq " + rightReg + ", " + reg);
            emit("sete " + reg + "b");
            emit("movzbq " + reg + "b, " + reg);
            break;
        case BinaryExprType::NOT_EQUAL:
            emit("cmpq " + rightReg + ", " + reg);
            emit("setne " + reg + "b");
            emit("movzbq " + reg + "b, " + reg);
            break;
	  default:
		break;
        }
        break;
    }
    }

    regTable.registerFree(rightReg);
    return reg;
}

std::string CodeGeneration::generateFunctionCall(std::shared_ptr<FunctionCallExpr> funcExpr)
{
    const auto& args = funcExpr->getArguments();

    // Save caller saved registers
    emit("pushq %r10");  // Only need to save r10, r11 as they are caller saved
    emit("pushq %r11");  // Other caller saved regs (rdi,rsi,rdx,rcx,r8,r9) will be used for args

    // Track registers used for arguments
    int intRegCount = 0;
    int xmmRegCount = 0;
    int stackArgs = 0;

    // First, count how many stack arguments we'll need to reserve space for
    for (const auto& arg : args)
    {
        if (arg->getExpressionType() == TypeKind::REAL)
        {
            if (xmmRegCount >= 8) stackArgs++;
            xmmRegCount++;
        }
        else
        {
            if (intRegCount >= 6) stackArgs++;
            intRegCount++;
        }
    }

    // Align stack number
    if (stackArgs > 0)
    {
        int stackSpace = ((stackArgs * 8 + 15) / 16) * 16;
        emit("subq $" + std::to_string(stackSpace) + ", %rsp");
    }

    // Reset counters for actual argument processing
    std::vector<std::string> intRegs = { "%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9" };
    int stackOffset = 0;
    intRegCount = 0;
    xmmRegCount = 0;

    for (const auto& arg : args)
    {
        std::string argReg = generateExpression(arg);

        if (arg->getExpressionType() == TypeKind::REAL)
        {
            // Move a float to the registers
            if (xmmRegCount < 8)
            {
                emit("movss " + argReg + ", %xmm" + std::to_string(xmmRegCount++));
            }
            else
            {
                emit("movss " + argReg + ", " + std::to_string(stackOffset) + "(%rsp)");
                stackOffset += 8;
            }
        }
        else
        {
            // Move an int to the registers
            if (intRegCount < 6)
            {
                emit("movq " + argReg + ", " + intRegs[intRegCount++]);
            }
            else
            {
                emit("movq " + argReg + ", " + std::to_string(stackOffset) + "(%rsp)");
                stackOffset += 8;
            }
        }
        regTable.registerFree(argReg);
    }

    // Call function
    emit("call " + funcExpr->getName());

    // Restore stack if we used it for arguments
    if (stackArgs > 0)
    {
        int stackSpace = ((stackArgs * 8 + 15) / 16) * 16;
        emit("addq $" + std::to_string(stackSpace) + ", %rsp");
    }

    // Restore caller-saved registers
    emit("popq %r11");
    emit("popq %r10");

    // Get return value into a new register based on return type
    std::string reg;
    switch (funcExpr->getExpressionType())
    {
    case TypeKind::REAL:
        reg = regTable.floatRegisterAllocate();
        emit("movss %xmm0, " + reg);
        break;
    case TypeKind::TEXT:
        reg = regTable.registerAllocate();
        emit("movq %rax, " + reg);
        break;
    default: // NUM, BOOL
        reg = regTable.registerAllocate();
        emit("movl %eax, " + reg);
        break;
    }
    return reg;
}

void CodeGeneration::generateNumberOut(std::string reg)
{
    // Convert number to string
    // Reserve 12 bytes on stack for number string (10 digits + sign + null)
    emit("subq $16, %rsp");  // Align to 16 bytes

    // Save registers we'll use
    emit("pushq %rax");
    emit("pushq %rcx");
    emit("pushq %rdx");
    emit("pushq %rdi");
    emit("pushq %rsi");
    emit("pushq %r8");
    emit("pushq %r9");

    // Move number to process
    emit("movl " + reg + ", %eax");
    emit("movq %rsi, %rsp");          // Get stack pointer
    emit("addq $71, %rsi");           // Skip saved registers to reach our buffer And the 16 byte buffer
    emit("movq %rsi, %rdi");          // Start at the end for digit conversion

    // Convert digits from right to left
    emit("movl $10, %ecx");           // Divisor for base 10
    std::string convertLoop = createLabel();
    emit(convertLoop + ":");
    emit("xorl %edx, %edx");          // Clear high bits for division
    emit("divl %ecx");                // Divide by 10
    emit("addb $48, %dl");            // Convert remainder to ASCII
    emit("movb %dl, (%rsi)");         // Store digit
    emit("decq %rsi");                // Move left in buffer
    emit("testl %eax, %eax");         // Check if more digits
    emit("jnz " + convertLoop);

    // Handle negative numbers after digits
    emit("testl " + reg + ", " + reg);
    std::string notNegative = createLabel();
    emit("jns " + notNegative);
    emit("movb $45, (%rsi)");         // Store '-' at current position
    emit("jmp " + notNegative);       // Skip decrementing rsi
    emit(notNegative + ":");

    // Calculate string length
    emit("movq %rdi, %rdx");   // End of buffer
    emit("subq %rsi, %rdx");   // Calculate length

    // Write to stdout everything else is already in the correct location
    emit("movq $1, %rax");     // sys_write
    emit("movq $1, %rdi");     // stdout
    emit("syscall");

    // Restore registers
    emit("popq %r9");
    emit("popq %r8");
    emit("popq %rsi");
    emit("popq %rdi");
    emit("popq %rdx");
    emit("popq %rcx");
    emit("popq %rax");

    emit("addq $16, %rsp");    // Restore stack
}

void CodeGeneration::generateNewLineOut()
{
    // Reserve stack space and maintain 16-byte alignment
    emit("subq $16, %rsp");

    // Save registers we'll modify
    emit("pushq %rax");
    emit("pushq %rdi");
    emit("pushq %rsi");
    emit("pushq %rdx");

    // Store newline character on stack
    emit("movq %rsp, %rsi");
    emit("addq $32, %rsi");      // Skip over saved registers
    emit("movb $10, (%rsi)");    // ASCII 10 is newline

    // Write syscall
    emit("movq $1, %rax");       // sys_write
    emit("movq $1, %rdi");       // stdout file descriptor
    emit("movq $1, %rdx");       // length = 1 byte

    emit("syscall");

    // Restore registers
    emit("popq %rdx");
    emit("popq %rsi");
    emit("popq %rdi");
    emit("popq %rax");

    // Restore stack
    emit("addq $16, %rsp");
}

void CodeGeneration::generateFloatOut(std::string reg)
{
    // Get the integer part using truncation
    std::string intReg = regTable.registerAllocate();
    emit("cvttss2si " + reg + ", " + intReg);

    // Print the integer part 
    generateNumberOut(intReg);
    regTable.registerFree(intReg);

    // Print decimal point
    emit("subq $16, %rsp"); // Reserve aligned stack space
    emit("pushq %rax"); // Save registers we'll modify
    emit("pushq %rdi");
    emit("pushq %rsi");
    emit("pushq %rdx");

    // Write the decimal point
    emit("movq %rsp, %rsi");      // Point to our stack space
    emit("addq $32, %rsi");       // Skip saved registers
    emit("movb $46, (%rsi)");     // Store '.' character

    emit("movq $1, %rax");        // sys_write
    emit("movq $1, %rdi");        // stdout
    emit("movq $1, %rdx");        // length is 1
    emit("syscall");

    // Restore registers
    emit("popq %rdx");
    emit("popq %rsi");
    emit("popq %rdi");
    emit("popq %rax");
    emit("addq $16, %rsp");

    // Now handle decimal part
    // Convert integer back to float and subtract from original to get just decimal part
    std::string tempFloatReg = regTable.floatRegisterAllocate();
    emit("cvtsi2ss " + intReg + ", " + tempFloatReg);    // Convert back to float
    emit("subss " + tempFloatReg + ", " + reg);          // Get just decimal part

    // Multiply by 1000 to get 3 decimal places
    emit("mulss .float_1000(%rip), " + reg);

    // Convert to integer
    std::string decimalReg = regTable.registerAllocate();
    emit("cvtss2si " + reg + ", " + decimalReg);

    // Ensure positive (in case of negative numbers, we already handled sign in integer part)
    emit("andl $0x7FFFFFFF, " + decimalReg);

    // Print the three decimal digits, handling leading zeros
    generateNumberOut(decimalReg);

    // Clean up registers
    regTable.registerFree(tempFloatReg);
    regTable.registerFree(decimalReg);
}
