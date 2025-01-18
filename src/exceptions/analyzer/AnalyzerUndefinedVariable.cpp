#include "AnalyzerUndefinedVariable.h"

AnalyzerUndefinedVariable::AnalyzerUndefinedVariable(const std::string& variableName, int lineNumber) : AnalyzerException("Undefined variable '" + variableName + "'.", lineNumber)
{
}
