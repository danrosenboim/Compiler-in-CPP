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

void Lexer::advance()
{
	// Read next token
	currentToken = scanner->getNextToken();
}

bool Lexer::match(TokenType type)
{
	// Advance if we match correctly
	if(currentToken->type == type)
	{
		advance();
		return true;
	}
	return false;
}

void Lexer::expect(TokenType type)
{
	// Check if the result equals the expectation
	if(!match(type))
	{
		// TODO make parser exceptions
		throw std::runtime_error("Unexpected");
	}
}

static std::shared_ptr<Node> Lexer::createNode(NodeType type, TokenType tokenType, int lineNumber)
{
	return std::make_shared<Node>(type, std::make_unique<Token>(tokenType, lineNumber));
}

static std::shared_ptr<Node> Lexer::createNode(NodeType type, TokenType tokenType)
{
	// Calls the create node function without the line number
	return createNode(type, tokenType, currentToken.getLineNumber());
}

static std::shared_ptr<Node> Lexer::createNode(NodeType type)
{
	// No token
	return std::make_shared<Node>(type, nullptr);
}

// Function -> Function Type IDENTIFIER "(" Parameters? ")" Block
std::shared_ptr<Node> Lexer::parseFunction()
{
	auto functionNode = std::make_shared<Node>(NodeType::FUNCTION);
	
	// Type
	functionNode->addChild(parseType());

	// Identifier
	functionNode->addChild(std::make_shared<Node>(NodeType::IDENTIFIER, Token(TokenType::IDENTIFIER, currentToken.getLineNumber()));
	expect(TokenType::IDENTIFIER);
	functionNode->addChild(parseType());
}

// Type -> "num" | "text" | "real" | "bool"
std::shared_ptr<Node> Lexer::parseType()
{
	auto typeNode = std::make_shared<Node>(NodeType::TYPE, Token(currentToken.getTag(), currentToken.getLineNumber());

	// Check if the user inputted the expected input
	if(!match(TokenType::INT) && !match(TokenType::STRING) && !match(TokenType::FLOAT) && !match(TokenType::BOOL))
	{
		// TODO make parser exceptions
		throw std::runtime_error("Unexpected");
	}

	return typeNode;
}



