#pragma once
#include "AnalyzerException.h"

class AnalyzerCannotCallVariable : public AnalyzerException
{
public:
	AnalyzerCannotCallVariable(const std::string& name, int lineNumber);
};