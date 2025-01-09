#include "Analyzer.h"

Analyzer::Analyzer() : symbolTable(std::make_unique<SymbolTable>()), currentFunctionReturnType(TypeKind::NUM), currentFunctionName("")
{
}

void Analyzer::analyze(std::shared_ptr<ProgramNode> programNode)
{
	symbolTable->enterScope();

	// Loop through all the function declarations and add them
	for (auto& func : programNode->getFunctions())
	{
		currentFunctionName = func->getName();
		registerFunction(func);
	}

	currentFunctionName = "";

	// Now we can loop over the funcitons and then the statements
	// We do this in this order because the statements may use functions
	for (auto& func : programNode->getFunctions())
	{
		currentFunctionName = func->getName();
		analyzeFunction(func);
	}

	currentFunctionName = "";

	for (auto& statement : programNode->getStatements())
	{
		analyzeStatement(statement);
	}

	// Add global declarations to program node
	for (const auto& declaration : symbolTable->exitScope())
	{
		if (declaration.second->declarationNode != nullptr)
		{
			programNode->addDeclaration(declaration.second);
		}
	}

}

bool Analyzer::canConvert(TypeKind from, TypeKind to)
{
	// Text can only be used with each other
	if (from == TypeKind::TEXT || to == TypeKind::TEXT)
	{
		return from == to;
	}
	
	// Any other types can convert whenever needed
	return true;
}

TypeKind Analyzer::convertBinaryOperation(TypeKind type1, TypeKind type2, std::shared_ptr<ExpressionNode> expr1, std::shared_ptr<ExpressionNode> expr2)
{
	if (type1 == type2)
	{
		return type1;
	}

	// Float operations
	if (type1 == TypeKind::REAL)
	{
		expr2->markForConversion(TypeKind::REAL);
		return TypeKind::REAL;
	}

	if (type2 == TypeKind::REAL)
	{
		expr1->markForConversion(TypeKind::REAL);
		return TypeKind::REAL;
	}

	// Int operations
	if (type1 == TypeKind::NUM)
	{
		expr2->markForConversion(TypeKind::NUM);
		return TypeKind::NUM;
	}

	if (type2 == TypeKind::NUM)
	{
		expr1->markForConversion(TypeKind::NUM);
		return TypeKind::NUM;
	}

	// Error in code
	throw CompilerException("Real compiler error", 0);
}

std::string Analyzer::typeKindToString(TypeKind type)
{
	switch (type)
	{
	case TypeKind::NUM: return "num";
	case TypeKind::BOOL: return "bool";
	case TypeKind::TEXT: return "text";
	case TypeKind::REAL: return "real";
	default:
		return "unknown";
	}
}

void Analyzer::registerFunction(std::shared_ptr<FunctionNode> func)
{
	// Check for function redefinition
	if (symbolTable->tableLookup(func->getName()) != nullptr)
	{
		throw AnalyzerFunctionRedefined(func->getName(), func->getLineNumber());
	}

	// Register function in global scope
	Symbol funcSymbol(SymbolType::GLOBAL, func->getReturnType(), func->getName(), 0);
	funcSymbol.functionNode = func;
	symbolTable->addEntryToLatest(funcSymbol);
}

void Analyzer::analyzeFunction(std::shared_ptr<FunctionNode> func)
{
	// Setting the current return type
	currentFunctionReturnType = func->getReturnType();

	// Telling the symbol table that we have entered a scope
	symbolTable->enterScope();

	// Register parameters
	for (const auto& param : func->getParameters())
	{
		Symbol paramSymbol(SymbolType::PARAM, param->getType(), param->getIdentifier(), symbolTable->getLatestSize() + 1);
		symbolTable->addEntryToLatest(paramSymbol);
	}

	// Loop through the statements and analyze them
	analyzeBlock(func->getBody());
}

void Analyzer::analyzeBlock(std::shared_ptr<BlockNode> block)
{
	// Loop through the statements and analyze them
	for (auto& stmt : block->getStatements())
	{
		analyzeStatement(stmt);
	}

	// Adding all the symbols to the block
	for (const auto& dcl : symbolTable->exitScope())
	{
		block->addDeclaration(dcl.second);
	}
}

void Analyzer::analyzeStatement(std::shared_ptr<StatementNode> statement)
{
	switch (statement->getStatementType())
	{
	// Analyze the statement using the statementType
	case StatementType::ASSIGNMENT:
		analyzeAssignment(std::dynamic_pointer_cast<AssignmentStatementNode>(statement));
		break;
	case StatementType::DECLARATION:
		analyzeDeclaration(std::dynamic_pointer_cast<DeclarationStatementNode>(statement));
		break;
	case StatementType::FOR:
		analyzeFor(std::dynamic_pointer_cast<ForStatementNode>(statement));
		break;
	case StatementType::IF:
		analyzeIf(std::dynamic_pointer_cast<IfStatementNode>(statement));
		break;
	case StatementType::IN:
		analyzeIn(std::dynamic_pointer_cast<InStatementNode>(statement));
		break;
	case StatementType::OUT:
		analyzeOut(std::dynamic_pointer_cast<OutStatementNode>(statement));
		break;
	case StatementType::RETURN:
		analyzeReturn(std::dynamic_pointer_cast<ReturnStatementNode>(statement));
		break;
	case StatementType::ERROR:
	default:
		// If it reaches here its an error in the compiler
		throw CompilerException("Real compiler error", 0);
	}
}

void Analyzer::analyzeAssignment(std::shared_ptr<AssignmentStatementNode> assignment)
{
	// Check if variable exists
	std::shared_ptr<Symbol> symbol = symbolTable->tableLookup(assignment->getIdentifier());
	if (symbol == nullptr)
	{
		throw AnalyzerUndefinedVariable(assignment->getIdentifier(), assignment->getLineNumber());
	}

	// Analyze the expression and get its type
	TypeKind exprType = analyzeExpression(assignment->getExpression());

	// Check if types are compatible
	if (!canConvert(exprType, symbol->varType))
	{
		throw AnalyzerCannotConvert(typeKindToString(exprType), typeKindToString(symbol->varType), assignment->getLineNumber());
	}

	// Mark for conversion if needed
	if (exprType != symbol->varType)
	{
		assignment->getExpression()->markForConversion(symbol->varType);
	}
}

void Analyzer::analyzeDeclaration(std::shared_ptr<DeclarationStatementNode> declaration)
{
	// Check for variable redefinition in current scope
	if (symbolTable->currentScopeLookup(declaration->getIdentifier()) != nullptr)
	{
		throw AnalyzerVarDefined(declaration->getIdentifier(), declaration->getLineNumber());
	}

	// Add to symbol table
	Symbol varSymbol((symbolTable->getScopeLevel() == 0) ? SymbolType::GLOBAL : SymbolType::LOCAL, declaration->getType(),
		declaration->getIdentifier(), symbolTable->getLatestSize() + 1);
	varSymbol.declarationNode = declaration;

	symbolTable->addEntryToLatest(varSymbol);

	// If there's an initializer, check types
	if (declaration->getInitializer())
	{
		TypeKind initType = analyzeExpression(declaration->getInitializer());
		if (!canConvert(initType, declaration->getType()))
		{
			throw AnalyzerCannotConvert(typeKindToString(initType), typeKindToString(declaration->getType()), declaration->getLineNumber());
		}

		if (initType != declaration->getType())
		{
			declaration->getInitializer()->markForConversion(declaration->getType());
		}
	}
}

void Analyzer::analyzeFor(std::shared_ptr<ForStatementNode> forNode)
{
	symbolTable->enterScope();

	// Create iteration variable
	Symbol iterationVar(SymbolType::LOCAL, TypeKind::NUM, forNode->getVariableName(), symbolTable->getScopeLevel());
	symbolTable->addEntryToLatest(iterationVar);

	// Analyze initialization expression
	TypeKind initType = analyzeExpression(forNode->getInitExpr());
	if (!canConvert(initType, iterationVar.varType))
	{
		throw AnalyzerCannotConvert(typeKindToString(initType), typeKindToString(iterationVar.varType), forNode->getLineNumber());
	}

	// Mark for conversion if needed
	if (initType != iterationVar.varType)
	{
		forNode->getInitExpr()->markForConversion(iterationVar.varType);
	}

	TypeKind condType = analyzeExpression(forNode->getCondition());
	if (!canConvert(condType, TypeKind::BOOL))
	{
		throw AnalyzerCannotConvert(typeKindToString(condType), "bool", forNode->getCondition()->getLineNumber());
	}
	// Mark for conversion if needed
	if (condType != TypeKind::BOOL)
	{
		forNode->getCondition()->markForConversion(TypeKind::BOOL);
	}

	// Analyze the loop body
	analyzeBlock(forNode->getBody());
}

void Analyzer::analyzeIf(std::shared_ptr<IfStatementNode> ifNode)
{
	TypeKind condType = analyzeExpression(ifNode->getCondition());
	if (!canConvert(condType, TypeKind::BOOL))
	{
		throw AnalyzerCannotConvert(typeKindToString(condType), "bool", ifNode->getCondition()->getLineNumber());
	}
	// Mark for conversion if needed
	if (condType != TypeKind::BOOL)
	{
		ifNode->getCondition()->markForConversion(TypeKind::BOOL);
	}

	symbolTable->enterScope();
	analyzeBlock(ifNode->getBody());

	// Analyzing the else block part
	if (ifNode->getElseBlock())
	{
		symbolTable->enterScope();
		analyzeBlock(ifNode->getElseBlock());
	}
}

void Analyzer::analyzeIn(std::shared_ptr<InStatementNode> inNode)
{
	// Check if variable exists
	std::shared_ptr<Symbol> varSymbol = symbolTable->tableLookup(inNode->getIdentifier());
	if (varSymbol == nullptr)
	{
		throw AnalyzerUndefinedVariable(inNode->getIdentifier(), inNode->getLineNumber());
	}
	if (varSymbol->varType == TypeKind::TEXT || varSymbol->varType == TypeKind::REAL)
	{
		throw AnalyzerCannotConvert(typeKindToString(varSymbol->varType), typeKindToString(TypeKind::NUM), inNode->getLineNumber());
	}
}

void Analyzer::analyzeOut(std::shared_ptr<OutStatementNode> outNode)
{
	analyzeExpression(outNode->getExpression());
}

void Analyzer::analyzeReturn(std::shared_ptr<ReturnStatementNode> returnNode)
{
	// Make sure the return is in a scope
	if (currentFunctionName == "")
	{
		throw AnalyzerCannotReturnInGlobal(returnNode->getLineNumber());
	}

	TypeKind returnType = analyzeExpression(returnNode->getExpression());
	returnNode->setFunctionName(currentFunctionName);

	// Check if return type matches function's declared return type
	if (!canConvert(returnType, currentFunctionReturnType))
	{
		throw AnalyzerCannotConvert(typeKindToString(returnType), typeKindToString(currentFunctionReturnType), returnNode->getLineNumber());
	}

	// Mark for conversion if needed
	if (returnType != currentFunctionReturnType)
	{
		returnNode->getExpression()->markForConversion(currentFunctionReturnType);
	}
}

TypeKind Analyzer::analyzeExpression(std::shared_ptr<ExpressionNode> expression)
{
	TypeKind resultType = TypeKind::NUM;

	// Check what expression it is
	switch (expression->getExpressionVariant())
	{
	case ExpressionType::BINARY:
		resultType = analyzeBinaryExpression(std::dynamic_pointer_cast<BinaryExpr>(expression));
		break;

	case ExpressionType::NOT:
		resultType = analyzeNot(std::dynamic_pointer_cast<NotExpr>(expression));
		break;

	case ExpressionType::NUMBER:
		resultType = TypeKind::NUM;
		break;
	case ExpressionType::REAL:
		resultType = TypeKind::REAL;
		break;
	case ExpressionType::BOOL:
		resultType = TypeKind::BOOL;
		break;
	case ExpressionType::STRING:
		resultType = TypeKind::TEXT;
		break;

	case ExpressionType::IDENTIFIER:
		resultType = analyzeIdentifier(std::dynamic_pointer_cast<IdentifierExpr>(expression));
		break;

	case ExpressionType::FUNC_CALL:
		resultType = analyzeFunctionCall(std::dynamic_pointer_cast<FunctionCallExpr>(expression));
		break;

	case ExpressionType::ERROR:
	default:
		// If it reaches here its an error in the compiler
		throw CompilerException("Real compiler error", 0);
	}

	expression->setCurrentType(resultType);
	return resultType;
}

TypeKind Analyzer::analyzeBinaryExpression(std::shared_ptr<BinaryExpr> expression)
{
	TypeKind leftType = analyzeExpression(expression->getLeft());
	TypeKind rightType = analyzeExpression(expression->getRight());

	switch (expression->getType())
	{
	case BinaryExprType::ADD:
	case BinaryExprType::SUB:
	case BinaryExprType::MUL:
	case BinaryExprType::DIV:
		// These operations are only valid for numeric types

		if (leftType == TypeKind::TEXT || rightType == TypeKind::TEXT)
		{
			throw AnalyzerCannotPerformOnText(expression->getLineNumber());
		}
		if (leftType == TypeKind::BOOL && rightType == TypeKind::BOOL)
		{
			expression->getLeft()->markForConversion(TypeKind::NUM);
			expression->getRight()->markForConversion(TypeKind::NUM);
			return TypeKind::NUM;
		}
		return convertBinaryOperation(leftType, rightType, expression->getLeft(), expression->getRight());

	case BinaryExprType::EQUAL_EQUAL:
	case BinaryExprType::NOT_EQUAL:
		if (leftType == TypeKind::TEXT || rightType == TypeKind::TEXT)
		{
			if (leftType != rightType)
			{
				throw AnalyzerCannotPerformOnText(expression->getLineNumber());
			}
			return TypeKind::BOOL;
		}

		convertBinaryOperation(leftType, rightType, expression->getLeft(), expression->getRight());

		return TypeKind::BOOL;


	case BinaryExprType::GREATER:
	case BinaryExprType::GREATER_EQUAL:
	case BinaryExprType::LESS:
	case BinaryExprType::LESS_EQUAL:
		if (leftType == TypeKind::TEXT || rightType == TypeKind::TEXT)
		{
			throw AnalyzerCannotPerformOnText(expression->getLineNumber());
		}

		convertBinaryOperation(leftType, rightType, expression->getLeft(), expression->getRight());

		return TypeKind::BOOL;

	default:
		// If it reaches here its an error in the compiler
		throw CompilerException("Real compiler error", 0);
	}

}

TypeKind Analyzer::analyzeIdentifier(std::shared_ptr<IdentifierExpr> idExpr)
{
	std::shared_ptr<Symbol> symbol = symbolTable->tableLookup(idExpr->getName());
	if (symbol == nullptr)
	{
		throw AnalyzerUndefinedVariable(idExpr->getName(), idExpr->getLineNumber());
	}

	return symbol->varType;
}

TypeKind Analyzer::analyzeFunctionCall(std::shared_ptr<FunctionCallExpr> funcExpr)
{
	// Look up the function in symbol table
	auto funcSymbol = symbolTable->tableLookup(funcExpr->getName());
	if (!funcSymbol)
	{
		throw AnalyzerUndefinedVariable(funcExpr->getName(), funcExpr->getLineNumber());
	}

	if (!funcSymbol->functionNode)
	{
		throw AnalyzerCannotCallVariable(funcExpr->getName(), funcExpr->getLineNumber());
	}

	// Check argument count
	auto params = funcSymbol->functionNode->getParameters();
	auto args = funcExpr->getArguments();
	if (params.size() != args.size())
	{
		throw AnalyzerInvalidArgCount(args.size(), params.size(), funcExpr->getLineNumber());
	}

	// Check each argument type against parameter type
	for (size_t i = 0; i < args.size(); i++)
	{
		TypeKind argType = analyzeExpression(args[i]);
		TypeKind paramType = params[i]->getType();

		if (!canConvert(argType, paramType))
		{
			throw AnalyzerCannotConvert(typeKindToString(argType), typeKindToString(paramType), funcExpr->getLineNumber());
		}

		// Mark for conversion if needed
		if (argType != paramType)
		{
			args[i]->markForConversion(paramType);
		}
	}

	return funcSymbol->varType; // Return type of function
}

TypeKind Analyzer::analyzeNot(std::shared_ptr<NotExpr> notExpr)
{
	TypeKind expressionType = analyzeExpression(notExpr->getExpression());
	if (!canConvert(expressionType, TypeKind::BOOL))
	{
		throw AnalyzerCannotConvert(typeKindToString(expressionType), "bool", notExpr->getLineNumber());
	}
	if (expressionType != TypeKind::BOOL)
	{
		notExpr->getExpression()->markForConversion(TypeKind::BOOL);
	}
	return TypeKind::BOOL;
}
