#pragma once
#include "LexerException.h"

// This exception is called if the user enters an invalid float
class LexerInvalidFloat : public LexerException
{
public:
	LexerInvalidFloat(int lineNumber);
};
