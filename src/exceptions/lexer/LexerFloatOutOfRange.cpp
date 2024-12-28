#include "LexerFloatOutOfRange.h"

LexerFloatOutOfRange::LexerFloatOutOfRange(const std::string& realNumber, int lineNumber) : LexerException("Float too big: '" + realNumber + "'", lineNumber)
{
}

