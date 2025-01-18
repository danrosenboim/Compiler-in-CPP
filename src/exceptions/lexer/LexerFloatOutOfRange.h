#pragma once
#include "LexerException.h"

// This exception is called if the user enters a float that is too big
class LexerFloatOutOfRange : public LexerException
{
public:
	LexerFloatOutOfRange(const std::string& realNumber, int lineNumber);
};
