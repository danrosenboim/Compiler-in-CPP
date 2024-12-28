#include "Parser.h"

Parser::Parser(std::shared_ptr<Lexer> scanner) : scanner(scanner)
{
	// Get initial token
	advance();
}


std::shared_ptr<Node> Parser::parseProgram()
{
	auto programHead = std::make_shared<Node>(Token(TokenType::PROGRAM, 0));
}

void Lexer::advance()
{
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


