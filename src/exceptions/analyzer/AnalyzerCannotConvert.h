#pragma once
#include "AnalyzerException.h"

class AnalyzerCannotConvert : AnalyzerException
{
public:
	AnalyzerCannotConvert(const std::string& from, const std::string& to, int lineNumber);
};