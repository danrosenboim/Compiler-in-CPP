#include <iostream>
#include "lexer/Lexer.h"

int main()
{
	Lexer lexer("testing.dan");
	try
	{
	while(true)
	{
		Token toke = lexer.getNextToken();
		if(toke.getTag() == TokenType::WHITESPACE || toke.getTag() == TokenType::COMMENT)
		{
			continue;
		}
		std::cout << "Token: " << toke << std::endl;
		if(toke.getTag() == TokenType::END_OF_FILE)
		{
			exit(0);
		}
	}
	}
	catch(const std::exception& s)
	{
		std::cout << s.what() << std::endl;
	}
	return 0;
}
