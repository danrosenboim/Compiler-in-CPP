#pragma once
#include "AnalyzerException.h"

class AnalyzerFunctionRedefined : AnalyzerException
{
public:
	AnalyzerFunctionRedefined(const std::string& functionName, int lineNumber);
};