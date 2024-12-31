#pragma once
#include "AnalyzerException.h"

class AnalyzerFunctionRedefined : public AnalyzerException
{
public:
	AnalyzerFunctionRedefined(const std::string& functionName, int lineNumber);
};