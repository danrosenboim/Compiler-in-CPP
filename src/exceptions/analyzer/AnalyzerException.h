#pragma once
#include "../CompilerException.h"

// Base class for analyzer exception inheritence
class AnalyzerException : public CompilerException
{
public:
	AnalyzerException(const std::string& msg, int lineNumber);
};
