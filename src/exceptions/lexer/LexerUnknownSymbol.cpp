#include "LexerUnknownSymbol.h"

LexerUnknownSymbol::LexerUnknownSymbol(char symbol, int lineNumber) : LexerException("Unknown Symbol '" + std::string(1, symbol) + "'", lineNumber) {}

