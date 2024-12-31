#pragma once
#include "AnalyzerException.h"

class AnalyzerCannotPerformOnText : public AnalyzerException
{
public:
	AnalyzerCannotPerformOnText(int lineNumber);
};