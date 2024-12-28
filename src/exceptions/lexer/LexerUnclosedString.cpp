#include "LexerUnclosedString.h"

LexerUnclosedString::LexerUnclosedString(int lineNumber) : LexerException("Unclosed string", lineNumber)
{}
