#include "Parser.h"

Parser::Parser(const std::string& filePath) : scanner(std::make_shared<Lexer>(filePath)), currentToken(nullptr)
{
	
}




