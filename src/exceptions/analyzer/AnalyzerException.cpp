#include "AnalyzerException.h"

AnalyzerException::AnalyzerException(const std::string& msg, int lineNumber) : CompilerException(msg, lineNumber)
{
	
}
