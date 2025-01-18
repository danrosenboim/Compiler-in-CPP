#include "AnalyzerFunctionRedefined.h"

AnalyzerFunctionRedefined::AnalyzerFunctionRedefined(const std::string& functionName, int lineNumber) : AnalyzerException("Function '" + functionName + "' is already defined", lineNumber)
{
}
