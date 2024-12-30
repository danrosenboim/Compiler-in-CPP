#pragma once
#include "AnalyzerException.h"

class AnalyzerCannotReturnInGlobal : public AnalyzerException
{
public:
	AnalyzerCannotReturnInGlobal(int lineNumber);
};