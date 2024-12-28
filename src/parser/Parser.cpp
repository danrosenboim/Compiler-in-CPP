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
	// Read next token
	currentToken = scanner->getNextToken();
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

// Fo
