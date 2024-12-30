#include "AnalyzerCannotPerformOnText.h"

AnalyzerCannotPerformOnText::AnalyzerCannotPerformOnText(int lineNumber) : AnalyzerException("Cannot perform this operation on a text", lineNumber)
{
}
