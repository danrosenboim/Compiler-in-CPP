#pragma once
#include "AnalyzerException.h"

class AnalyzerInvalidArgCount : public AnalyzerException
{
public:
	AnalyzerInvalidArgCount(int got, int expected, int lineNumber);
};