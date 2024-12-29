#pragma once
#include "../CompilerException.h"

// Base class for parser exception inheritence
class ParserException : public CompilerException
{
public:
	ParserException(const std::string& msg, int lineNumber);
}
