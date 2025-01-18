#pragma once
#include "LexerException.h"

// This exception is called if the user enters a int that is too big
class LexerIntOutOfRange : public LexerException
{
public:
	LexerIntOutOfRange(const std::string& realNumber, int lineNumber);
};
