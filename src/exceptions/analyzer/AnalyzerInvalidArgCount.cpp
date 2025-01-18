#include "AnalyzerInvalidArgCount.h"

AnalyzerInvalidArgCount::AnalyzerInvalidArgCount(int got, int expected, int lineNumber) : AnalyzerException("Invalid arg count, expected " + std::to_string(expected) + ", got " + std::to_string(got), lineNumber)
{
}
