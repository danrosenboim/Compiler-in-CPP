#pragma once
#include "AnalyzerException.h"

class AnalyzerVarDefined : public AnalyzerException
{
public:
	AnalyzerVarDefined(const std::string& varName, int lineNumber);
};