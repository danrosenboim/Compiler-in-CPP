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
	auto programHead = std::make_shared<Node>(NodeType::PROGRAM, Token(TokenType::NODE, 0));

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


// Function -> Function IDENTIFIER "(" Parameters? ")" Block
std::shared_ptr<Node> Lexer::parseFunction()
{
	auto functionNode = std::make_shared<Node>(NodeType::FUNCTION, Token(TokenType::NODE, currentToken.getLineNumber());
}




