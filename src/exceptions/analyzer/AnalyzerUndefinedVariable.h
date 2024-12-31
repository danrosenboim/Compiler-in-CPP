#pragma once
#include "AnalyzerException.h"

class AnalyzerUndefinedVariable : public AnalyzerException
{
public:
	AnalyzerUndefinedVariable(const std::string& variableName, int lineNumber);
};