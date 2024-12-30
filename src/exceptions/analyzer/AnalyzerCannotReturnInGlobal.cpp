#include "AnalyzerCannotReturnInGlobal.h"

AnalyzerCannotReturnInGlobal::AnalyzerCannotReturnInGlobal(int lineNumber) : AnalyzerException("Cannot return when not in a scope.", lineNumber)
{
}
