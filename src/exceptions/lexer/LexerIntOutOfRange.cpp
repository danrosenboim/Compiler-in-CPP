#include "LexerIntOutOfRange.h"

LexerIntOutOfRange::LexerIntOutOfRange(const std::string& realNumber, int lineNumber) : LexerException("Int too big '" + realNumber + "'", lineNumber)
{
}

