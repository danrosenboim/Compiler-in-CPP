#include "LexerInvalidInt.h"

LexerInvalidInt::LexerInvalidInt(int lineNumber) : LexerException("Invalid int", lineNumber)
{
}

