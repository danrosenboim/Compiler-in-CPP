#include "AnalyzerVarDefined.h"

AnalyzerVarDefined::AnalyzerVarDefined(const std::string& varName, int lineNumber) : AnalyzerException("Variable '" + varName + "' is already defined.", lineNumber)
{
}
