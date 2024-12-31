#include "AnalyzerCannotCallVariable.h"

AnalyzerCannotCallVariable::AnalyzerCannotCallVariable(const std::string& name, int lineNumber) : AnalyzerException("Cannot call '" + name + "', it is a variable not a function.", lineNumber)
{
}
