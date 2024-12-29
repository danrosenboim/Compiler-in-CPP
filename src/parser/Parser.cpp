#include "Parser.h"

Parser::Parser(std::shared_ptr<Lexer> scanner) : scanner(scanner)
{
	// Get initial token
	advance();
}


// Program -> ( Function | Statement )*
std::shared_ptr<Node> Parser::parseProgram()
{
	// Setting up AST head
	auto programHead = createNode(NodeType::PROGRAM);

	// Continue parsing the program until its over
	while(currentToken.getTag() != TokenType::END_OF_FILE)
	{
		// A program can only be a function or statement
		if(currentToken.getTag() == TokenType::FUNCTION)
		{
			programHead->addChild(parseFunction());
		}
		else
		{
			programHead->addChild(parseStatement());
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
	if(currentToken->type == type)
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
		// TODO make parser exceptions
		throw std::runtime_error("Unexpected");
	}
}

bool Parser::isComparisonOp(TokenType type)
{
	return type == TokenType::EQUAL_EQUAL ||
               type == TokenType::NOT_EQUAL ||
               type == TokenType::GREATER_EQUAL ||
               type == TokenType::LESS_EQUAL ||
               type == TokenType::GREATER ||
               type == TokenType::LESS;
}

static std::shared_ptr<Node> Parser::createNode(NodeType type, Token token)
{
	return std::make_shared<Node>(type, std::make_unique<Token>(token));
}

static std::shared_ptr<Node> Parser::createNode(NodeType type, TokenType tokenType, int lineNumber)
{
	return std::make_shared<Node>(type, std::make_unique<Token>(tokenType, lineNumber));
}

static std::shared_ptr<Node> Parser::createNode(NodeType type, TokenType tokenType)
{
	// Calls the create node function without the line number
	return createNode(type, tokenType, currentToken.getLineNumber());
}

static std::shared_ptr<Node> Parser::createNode(NodeType type)
{
	// No token
	return std::make_shared<Node>(type, nullptr);
}

// Function -> Function Type IDENTIFIER "(" Parameters? ")" Block
std::shared_ptr<Node> Parser::parseFunction()
{
	auto functionNode = createNode(NodeType::FUNCTION);
	
	// Type
	functionNode->addChild(parseType());

	// Identifier
	functionNode->addChild(parseIdentifier());

	expect(TokenType::LEFT_PAREN);

	if(currentToken.getTag() != TokenType::RIGHT_PAREN)
	{
		functionNode->addChild(parseParameters());
	}

	// Right paren
	advance();

	functionNode->addChild(parseBlock());

	return functionNode;
}

// Type -> "num" | "text" | "real" | "bool"
std::shared_ptr<Node> Parser::parseType()
{
	auto typeNode = createNode(NodeType::TYPE, currentToken.getTag());

	// Check if the user inputted the expected input
	if(!match(TokenType::INT) && !match(TokenType::STRING) && !match(TokenType::FLOAT) && !match(TokenType::BOOL))
	{
		// TODO make parser exceptions
		throw std::runtime_error("Unexpected");
	}

	return typeNode;
}

// IDENTIFIER
std::shared_ptr<Node> Parser::parseIdentifier()
{
	auto identifierNode = createNode(NodeType::IDENTIFIER, currentToken);
	
	expect(TokenType::IDENTIFIER);

	return identifierNode;
}

// Parameters -> Parameter ParameterTail*
// ParameterTail* -> "," Parameter
std::shared_ptr<Node> Parser::parseParameters()
{
	auto parametersNode = createNode(NodeType::PARAMETERS);
	parametersNode->addChild(parseParameter());

	while(currentToken.getTag() == TokenType::COMMA)
	{
		advance();
		parametersNode->addChild(parseParameter());
	}

	return parametersNode;
}

// Parameter -> Type IDENTIFIER
std::shared_ptr<Node> Parser::parseParameter()
{
	auto paramNode = createNode(NodeType::PARAMETER);

	paramNode->addChild(parseType());
	paramNode->addChild(parseIdentifier());

	return paramNode;
}

// Block -> "{" Statement* "}"
std::shared_ptr<Node> Parser::parseBlock()
{
	auto blockNode = createNode(NodeType::Block);

	expect(TokenType::LEFT_BRACE);
	
	while(currentToken.getTag() != TokenType::RIGHT_BRACE)
	{
		blockNode->addChild(parseStatement());
	}
	
	// Right brace
	advance();

	return blockNode;
}


// Statement -> ForStmt | IfStmt | ReturnStmt | OutStmt | InStmt | AssignmentStmt
std::shared_ptr<Node> Parser::parseStatement()
{
	switch(currentToken.getTag())
	{
	case TokenType::FOR:
		return parseForStatement();
	case TokenType::IF:
		return parseIfStatement();
	case TokenType::RETURN:
		return parseReturnStatement();
	case TokenType::OUT:
		return parseOutStatement();
	case TokenType::IN:
		return parseInStatement();
	default:
		return parseAssignmentStatement();
	}
}

// ForStmt -> "for" "(" IDENTIFIER "=" Expression ")" "until" "(" Expression ")" Block
std::shared_ptr<Node> Parser::parseForStatement()
{
	auto forNode = createNode(NodeType::FOR, TokenType::FOR);

	// Starting variable
	expect(TokenType::LEFT_PAREN);

	forNode->addChild(parseIdentifier());
	expect(TokenType::EQUAL);
	forNode->addChild(parseExpression());

	expect(TokenType::RIGHT_PAREN);

	expect(TokenType::UNTIL);
	
	// Condition
	expect(TokenType::LEFT_PAREN);
	forNode->addChild(parseExpression());
	expect(TokenType::RIGHT_PAREN);

	// Statements
	forNode->addChild(parseBlock());

	return forNode;
}

// IfStmt -> "if" "(" Expression ")" "then" Block ElsePart?
std::shared_ptr<Node> Parser::parseIfStatement()
{
	auto ifNode = createNode(NodeType::IF, TokenType::IF);
	
	// Expression
	expect(TokenType::LEFT_PAREN);
	ifNode->addChild(parseExpression());
	expect(TokenType::RIGHT_PAREN);
	
	expect(TokenType::THEN);
	
	// Block
	ifNode->addChild(parseBlock());

	// Else block
	if(currentToken.getTag() == TokenType::ELSE)
	{
		advance();
		ifNode->addChild(parseElsePart());
	}
	return ifNode;
}

// ElsePart -> "else" Block
std::shared_ptr<Node> Parser::parseElsePart()
{
	auto elsePartNode = createNode(NodeType::ELSE, TokenType::ELSE);
	elsePartNode->addChild(parseBlock());
	return elsePartNode;
}

// ReturnStmt -> "return" Expression ";"
std::shared_ptr<Node> Parser::parseReturnStatement()
{
	auto returnStatement = createNode(NodeType::RETURN, currentToken);
	advance();
	returnStatement->addChild(parseExpression());
	expect(TokenType::SEMICOLON);

	return returnStatement;
}

// OutStmt -> "out" Expression ";"
std::shared_ptr<Node> Parser::parseOutStatement()
{
	auto outStatement = createNode(NodeType::OUT, currentToken);
	advance();
	outStatement->addChild(parseExpression());
	expect(TokenType::SEMICOLON);

	return outStatement;
}

// InStmt -> "in" IDENTIFIER ";"
std::shared_ptr<Node> Parser::parseInStatement()
{
	auto inStatement = createNode(NodeType::IN, currentToken);
	advance();
	inStatemnet->addChild(parseIdentifier());
	expect(TokenType::SEMICOLON);

	return inStatement;
}

// AssignmentStmt -> IDENTIFIER "=" Expression ";"
std::shared_ptr<Node> Parser::parseAssignmentStmt()
{
	auto assignmentStatementNode = createNode(NodeType::ASSIGN);
	assignmentStatementNode->addChild(parseIdentifier());
	expect(TokenType::EQUAL);
	assignmentStatementNode->addChild(parseExpression());
	expect(TokenType::SEMICOLON);
	
	return assignmentStatementNode;
}

// Expression -> Term1 ComparisonTail?
std::shared_ptr<Node> Parser::parseExpression()
{
	auto expressionNode = parseTerm1();
	
	if(isComparisonOp(currentToken.getTag()))
	{
		auto exprNode = createNode(NodeType::EXPRESSION, currentToken);
		advance();
		exprNode->addChild(expressionNode);
		exprNode->addChild(parseTerm1());
		return exprNode;
	}

	return expressionNode;
}

// Term1 -> Term2 Term1Tail*
std::shared_ptr<Node> Parser::parseTerm1()
{
	auto left = parseTerm2();

	// While the term continues
	while(currentToken.getTag() == TokenType::PLUS || currentToken.getTag() == TokenType::MINUS)
	{
		// Create main op node and put left in it
		auto opNode = createNode(NodeType::TERM1, currentToken);
		advance();
		opNode->addChild(left);
		opNode->addChild(parseTerm2);
		left = opNode;
	}

	return left;
}

// Term2 -> Factor Term2Tail*
std::shared_ptr<Node> Parser::parseTerm2()
{
	auto left = parseFactor();

	// While the term continues
	while(currentToken.getTag() == TokenType::START || currentToken.getTag() == TokenType::SLASH)
	{
		// Create a main node and append both operands to it
		auto opNode = createNode(NodeType::TERM2, currentToken);
		advance();
		opNode->addChild(left);
		opNode->addChild(parseTerm1());
		left = opNode;
	}

	return left;
}

// Factor -> NUMBER | STRING | FLOAT | BOOL | IDENTIFIER | "(" Expression ")"
std::shared_ptr<Node> Paser::parseFactor()
{
	switch(currentToken.getTag())
	{
	// Incase of a literal advance and return
	case TokenType::NUMBER:
	case TokenType::TEXT:
	case TokenType::IDENTIFIER:
	case TokenType::BOOL:
	case TokenType::REAL:
		auto node = createNode(NodeType::FACTOR, currentToken);
		advance();
		return node;
	
	case TokenType::LEFT_PAREN:
		advance();
		auto expr = parseExpression();
		expect(TokenType::RIGHT_PAREN);
		return expr;
	default:
		// TODO: parser error
		throw std::runtime_error("PARSER ERROR");

	}
}

