#pragma once
#include "AnalyzerException.h"

class AnalyzerCannotPerformOnText : AnalyzerException
{
public:
	AnalyzerCannotPerformOnText(int lineNumber);
};