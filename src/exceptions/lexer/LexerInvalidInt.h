#pragma once
#include "LexerException.h"

// This exception is called if the user enters an invalid int
class LexerInvalidInt : public LexerException
{
public:
	LexerInvalidInt(int lineNumber);
};
