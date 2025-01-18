#pragma once
#include "LexerException.h"

// This exception is called if the user enters an unknown symbol
class LexerUnknownSymbol : public LexerException
{
public:
	LexerUnknownSymbol(char symbol, int lineNumber);

};
