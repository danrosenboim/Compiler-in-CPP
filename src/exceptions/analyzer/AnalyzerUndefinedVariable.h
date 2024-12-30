#pragma once
#include "AnalyzerException.h"

class AnalyzerUndefinedVariable : AnalyzerException
{
public:
	AnalyzerUndefinedVariable(const std::string& variableName, int lineNumber);
};