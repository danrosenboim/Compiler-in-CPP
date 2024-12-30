#pragma once
#include "AnalyzerException.h"

class AnalyzerInvalidArgCount : AnalyzerException
{
public:
	AnalyzerInvalidArgCount(int got, int expected, int lineNumber);
};