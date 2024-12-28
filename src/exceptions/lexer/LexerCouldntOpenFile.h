#pragma once
#include "LexerException.h"
#include <string>

// This exception is called when the source code file that was given could not be opened
class LexerCouldntOpenFile : public LexerException
{
public:
	LexerCouldntOpenFile(const std::string& fileName);

};
