#pragma once
#include "LexerException.h"

// This exception is called when the user left a string unclosed
class LexerUnclosedString : public LexerException
{
public:
	LexerUnclosedString(int lineNumber);
};

