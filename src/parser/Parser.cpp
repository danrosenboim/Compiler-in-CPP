#include "Parser.h"

Parser::Parser(std::shared_ptr<Lexer> scanner) : scanner(scanner), currentToken(TokenType::WHITESPACE, 0)
{
	// Get initial token
	advance();
}


// Program -> ( Function | Statement )*
std::unique_ptr<ProgramNode> Parser::parseProgram()
{
	// Setting up AST head
	auto programHead = std::make_unique<ProgramNode>(0);

	// Continue parsing the program until its over
	while(currentToken.getTag() != TokenType::END_OF_FILE)
	{
		// A program can only be a function or statement
		if(currentToken.getTag() == TokenType::FUNCTION)
		{
			programHead->addFunction(parseFunction());
		}
		else
		{
			programHead->addStatement(parseStatement());
		}
	}

	return programHead;
}

void Parser::advance()
{
	// Read next token that isnt whitespace or comments
	do
	{
		currentToken = scanner->getNextToken();
	} while(currentToken.getTag() == TokenType::WHITESPACE || currentToken.getTag() == TokenType::COMMENT);
}

bool Parser::match(TokenType type)
{
	// Advance if we match correctly
	if(currentToken.getTag() == type)
	{
		advance();
		return true;
	}
	return false;
}

void Parser::expect(TokenType type)
{
	// Check if the result equals the expectation
	if(!match(type))
	{
		throw ParserUnexpected(Token::typeToString(currentToken.getTag()), Token::typeToString(type), currentToken.getLineNumber());
	}
}

bool Parser::isComparisonOp(TokenType type, ExpressionType& exType)
{
	switch (type)
	{
	case TokenType::EQUAL_EQUAL:
		exType = ExpressionType::EQUAL_EQUAL;
		break;
	case TokenType::NOT_EQUAL:
		exType = ExpressionType::NOT_EQUAL;
		break;
	case TokenType::GREATER_EQUAL:
		exType = ExpressionType::GREATER_EQUAL;
		break;
	case TokenType::GREATER:
		exType = ExpressionType::GREATER;
		break;
	case TokenType::LESS_EQUAL:
		exType = ExpressionType::LESS_EQUAL;
		break;
	case TokenType::LESS:
		exType = ExpressionType::LESS;
		break;
	default: return false;
	}
	return true;
}


// Function -> Function Type IDENTIFIER "(" Parameters? ")" Block
std::shared_ptr<FunctionNode> Parser::parseFunction()
{
	auto functionNode = std::make_unique<FunctionNode>(currentToken.getLineNumber());

	advance();
	
	// Type
	functionNode->setReturnType(parseType());
	advance();

	// Identifier
	functionNode->setName(parseIdentifier());

	expect(TokenType::LEFT_PAREN);

	if(currentToken.getTag() != TokenType::RIGHT_PAREN)
	{
		std::vector<std::shared_ptr<ParameterNode>> parameters = parseParameters();
		functionNode->setParameters(parameters);
	}

	// Right paren
	expect(TokenType::RIGHT_PAREN);

	functionNode->setBody(parseBlock());

	return functionNode;
}

// Type -> "num" | "text" | "real" | "bool"
TypeKind Parser::parseType()
{
	// Return the correct type
	switch (currentToken.getTag())
	{
	case TokenType::INT: return TypeKind::NUM;
	case TokenType::BOOL: return TypeKind::BOOL;
	case TokenType::STRING: return TypeKind::TEXT;
	case TokenType::FLOAT: return TypeKind::REAL;
	default: throw ParserUnexpected(Token::typeToString(currentToken.getTag()), "type", currentToken.getLineNumber());
	}
	
}

// IDENTIFIER
std::string Parser::parseIdentifier()
{	
	std::string id = currentToken.getLexeme();
	
	// Make sure the current token is an identifier
	expect(TokenType::IDENTIFIER);

	return id;
}

// Parameters -> Parameter ParameterTail*
// ParameterTail* -> "," Parameter
std::vector<std::shared_ptr<ParameterNode>> Parser::parseParameters()
{
	std::vector<std::shared_ptr<ParameterNode>> parametersVector;

	// Initial parameter
	parametersVector.push_back(parseParameter());

	while(currentToken.getTag() == TokenType::COMMA)
	{
		advance();
		parametersVector.push_back(parseParameter());
	}

	return parametersVector;
}

// Parameter -> Type IDENTIFIER
std::shared_ptr<ParameterNode> Parser::parseParameter()
{
	auto paramNode = std::make_shared<ParameterNode>(currentToken.getLineNumber());

	paramNode->setType(parseType());
	advance();
	paramNode->setIdentifier(parseIdentifier());

	return paramNode;
}

// Block -> "{" Statement* "}"
std::shared_ptr<BlockNode> Parser::parseBlock()
{
	auto blockNode = std::make_shared<BlockNode>(currentToken.getLineNumber());

	expect(TokenType::LEFT_BRACE);
	
	while(currentToken.getTag() != TokenType::RIGHT_BRACE)
	{
		blockNode->addStatement(parseStatement());
	}
	
	// Right brace
	advance();

	return blockNode;
}


// Statement -> ForStmt | IfStmt | ReturnStmt | OutStmt | InStmt | DeclarationStmt | AssignmentStmt
std::shared_ptr<StatementNode> Parser::parseStatement()
{
	switch(currentToken.getTag())
	{
	case TokenType::FOR: return parseForStatement();
	case TokenType::IF: return parseIfStatement();
	case TokenType::RETURN: return parseReturnStatement();
	case TokenType::OUT: return parseOutStatement();
	case TokenType::IN: return parseInStatement();
	// Declaration or assignment
	case TokenType::INT:
	case TokenType::BOOL:
	case TokenType::STRING:
	case TokenType::FLOAT: return parseDeclarationStatement();
	default: return parseAssignmentStatement();
	}
}

// ForStmt -> "for" "(" IDENTIFIER "=" Expression ")" "until" "(" Expression ")" Block
std::shared_ptr<ForStatementNode> Parser::parseForStatement()
{
	auto forNode = std::make_shared<ForStatementNode>(currentToken.getLineNumber());
	
	advance();

	// Starting variable
	expect(TokenType::LEFT_PAREN);

	forNode->setVariableName(parseIdentifier());
	expect(TokenType::EQUAL);
	forNode->setInitExpr(parseExpression());

	expect(TokenType::RIGHT_PAREN);

	expect(TokenType::UNTIL);
	
	// Condition
	expect(TokenType::LEFT_PAREN);
	forNode->setCondition(parseExpression());
	expect(TokenType::RIGHT_PAREN);

	// Statements
	forNode->setBody(parseBlock());

	return forNode;
}

// IfStmt -> "if" "(" Expression ")" "then" Block ElsePart?
std::shared_ptr<IfStatementNode> Parser::parseIfStatement()
{
	std::shared_ptr<IfStatementNode> ifNode = std::make_shared<IfStatementNode>(currentToken.getLineNumber());
	
	advance();

	// Expression
	expect(TokenType::LEFT_PAREN);
	ifNode->setCondition(parseExpression());
	expect(TokenType::RIGHT_PAREN);
	
	expect(TokenType::THEN);
	
	// Block
	ifNode->setBody(parseBlock());

	// ElsePart -> "else" Block
	if(currentToken.getTag() == TokenType::ELSE)
	{
		advance();
		ifNode->setElseBlock(parseBlock());
	}
	return ifNode;
}

// ReturnStmt -> "return" Expression ";"
std::shared_ptr<ReturnStatementNode> Parser::parseReturnStatement()
{
	std::shared_ptr<ReturnStatementNode> returnStatement = std::make_shared<ReturnStatementNode>(currentToken.getLineNumber());
	advance();

	returnStatement->setExpression(parseExpression());
	expect(TokenType::SEMICOLON);

	return returnStatement;
}

// OutStmt -> "out" Expression ";"
std::shared_ptr<OutStatementNode> Parser::parseOutStatement()
{
	std::shared_ptr<OutStatementNode> outStatement = std::make_shared<OutStatementNode>(currentToken.getLineNumber());
	advance();

	outStatement->setExpression(parseExpression());
	expect(TokenType::SEMICOLON);

	return outStatement;
}

// InStmt -> "in" IDENTIFIER ";"
std::shared_ptr<InStatementNode> Parser::parseInStatement()
{
	auto inStatement = std::make_shared<InStatementNode>(currentToken.getLineNumber());
	advance();
	inStatement->setIdentifier(parseIdentifier());
	expect(TokenType::SEMICOLON);

	return inStatement;
}

// DeclarationStmt -> type IDENTIFIER ("=" Expression)? ";"
std::shared_ptr<DeclarationStatementNode> Parser::parseDeclarationStatement()
{
	auto declarationNode = std::make_shared<DeclarationStatementNode>(currentToken.getLineNumber());

	// Get the type and advance
	declarationNode->setType(parseType());
	advance();

	// Get the identifier
	declarationNode->setIdentifier(parseIdentifier());

	// Check for initialization
	if (currentToken.getTag() == TokenType::EQUAL)
	{
		advance();
		declarationNode->setInitializer(parseExpression());
	}

	expect(TokenType::SEMICOLON);
	return declarationNode;
}

// AssignmentStmt -> IDENTIFIER "=" Expression ";"
std::shared_ptr<AssignmentStatementNode> Parser::parseAssignmentStatement()
{
	auto assignmentStatementNode = std::make_shared<AssignmentStatementNode>(currentToken.getLineNumber());
	assignmentStatementNode->setIdentifier(parseIdentifier());
	expect(TokenType::EQUAL);
	assignmentStatementNode->setExpression(parseExpression());
	expect(TokenType::SEMICOLON);
	
	return assignmentStatementNode;
}

// Expression -> Term1 ComparisonTail?
std::shared_ptr<ExpressionNode> Parser::parseExpression()
{
	auto expressionNode = parseTerm1();
	ExpressionType exType;

	if(isComparisonOp(currentToken.getTag(), exType))
	{
		auto exprNode = std::make_shared<BinaryExpr>(currentToken.getLineNumber());

		exprNode->setType(exType);
		advance();
		exprNode->setLeft(std::move(expressionNode));
		exprNode->setRight(parseTerm1());
		return exprNode;
	}

	return expressionNode;
}

// Term1 -> Term2 Term1Tail*
std::shared_ptr<ExpressionNode> Parser::parseTerm1()
{
	auto left = parseTerm2();

	// While the term continues
	while(currentToken.getTag() == TokenType::PLUS || currentToken.getTag() == TokenType::MINUS)
	{
		// Create a main node and append both operands to it
		auto opNode = std::make_shared<BinaryExpr>(currentToken.getLineNumber());

		// Check what operator to do
		if (currentToken.getTag() == TokenType::PLUS)
		{
			opNode->setType(ExpressionType::ADD);
		}
		else
		{
			opNode->setType(ExpressionType::SUB);
		}
		advance();

		// Continue parsing
		opNode->setLeft(std::move(left));
		opNode->setRight(parseTerm2());
		left = std::move(opNode);
	}

	return left;
}

// Term2 -> Factor Term2Tail*
std::shared_ptr<ExpressionNode> Parser::parseTerm2()
{
	auto left = parseFactor();

	// While the term continues
	while(currentToken.getTag() == TokenType::STAR || currentToken.getTag() == TokenType::SLASH)
	{
		// Create a main node and append both operands to it
		auto opNode = std::make_shared<BinaryExpr>(currentToken.getLineNumber());
		
		// Check what operator to do
		if (currentToken.getTag() == TokenType::STAR)
		{
			opNode->setType(ExpressionType::MUL);
		}
		else
		{
			opNode->setType(ExpressionType::DIV);
		}
		advance();

		// Continue parsing
		opNode->setLeft(std::move(left));
		opNode->setRight(parseFactor());
		left = std::move(opNode);
	}

	return left;
}

// Factor -> NUMBER | STRING | FLOAT | BOOL | IDENTIFIER | "(" Expression ")"
std::shared_ptr<ExpressionNode> Parser::parseFactor()
{
	std::shared_ptr<ExpressionNode> expr = nullptr;
	std::shared_ptr<FunctionCallExpr> funcCall = nullptr;
	std::shared_ptr<NotExpr> notExpr = nullptr;
	std::shared_ptr<NumberExpr> numExpr = nullptr;
	std::shared_ptr<StringExpr> strExpr = nullptr;
	std::shared_ptr<BoolExpr> boolExpr = nullptr;
	std::shared_ptr<RealExpr> realExpr = nullptr;
	std::string name = "";


	switch(currentToken.getTag())
	{
	// Handle NOT operator
	case TokenType::NOT:
		notExpr = std::make_shared<NotExpr>(currentToken.getLineNumber());
		advance();
		notExpr->setExpression(parseFactor());
		return notExpr;

		
	// Incase of a literal advance and return
	case TokenType::NUMBER:
		numExpr = std::make_shared<NumberExpr>(currentToken.getLineNumber(), currentToken.getNumber());
		advance();
		return numExpr;
	case TokenType::TEXT:
		strExpr = std::make_shared<StringExpr>(currentToken.getLineNumber(), currentToken.getLexeme());
		advance();
		return strExpr;
	case TokenType::BOOL:
		boolExpr = std::make_shared<BoolExpr>(currentToken.getLineNumber(), currentToken.getBool());
		advance();
		return boolExpr;
	case TokenType::REAL:
		realExpr = std::make_shared<RealExpr>(currentToken.getLineNumber(), currentToken.getReal());
		advance();
		return realExpr;
	
	case TokenType::IDENTIFIER:
		name = currentToken.getLexeme();
		advance();

		// Check if it's a function call
		if (currentToken.getTag() == TokenType::LEFT_PAREN) {
			funcCall = std::make_shared<FunctionCallExpr>(currentToken.getLineNumber());
			funcCall->setName(name);

			advance();  // skip (

			// Parse arguments
			while (currentToken.getTag() != TokenType::RIGHT_PAREN) {
				funcCall->addArgument(parseExpression());

				// If the while loop continues expect comma
				if (currentToken.getTag() != TokenType::RIGHT_PAREN)
				{
					expect(TokenType::COMMA);
				}
			}

			advance();  // skip )
			return funcCall;
		}

		// If no parentheses, it's a regular identifier
		return std::make_shared<IdentifierExpr>(currentToken.getLineNumber() - 1, name);

	case TokenType::LEFT_PAREN:
		advance();
		expr = parseExpression();
		expect(TokenType::RIGHT_PAREN);
		return expr;

	default:
		throw ParserUnexpected(Token::typeToString(currentToken.getTag()), std::string("type or expression"), currentToken.getLineNumber());

	}
}

