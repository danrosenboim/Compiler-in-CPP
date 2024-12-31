#pragma once
#include "AnalyzerException.h"

class AnalyzerCannotConvert : public AnalyzerException
{
public:
	AnalyzerCannotConvert(const std::string& from, const std::string& to, int lineNumber);
};