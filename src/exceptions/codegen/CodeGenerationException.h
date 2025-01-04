#pragma once
#include "../CompilerException.h"

class CodeGenerationException : public CompilerException
{
public:
	CodeGenerationException(const std::string& msg, int lineNumber);
};