#include "LexerUnknownSymbol.h"

LexerUnknownSymbol::LexerUnknownSymbol(char symbol, int lineNumber) : LexerException(std::string("Unknown Symbol '") + symbol + "'", lineNumber) {}

