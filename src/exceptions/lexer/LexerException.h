#pragma once
#include "../CompilerException.h"

// Base class for lexer exception inheritence
class LexerException : public CompilerException
{
public:
	LexerException(const std::string& msg, int lineNumber);
};
