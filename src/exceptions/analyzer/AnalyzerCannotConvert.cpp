#include "AnalyzerCannotConvert.h"

AnalyzerCannotConvert::AnalyzerCannotConvert(const std::string& from, const std::string& to, int lineNumber) : AnalyzerException("Cannot convert '" + from + "' to '" + to + "'.", lineNumber)
{
}
