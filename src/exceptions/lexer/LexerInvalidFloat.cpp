#include "LexerInvalidFloat.h"

LexerInvalidFloat::LexerInvalidFloat(int lineNumber) : LexerException("Invalid float", lineNumber)
{
}

