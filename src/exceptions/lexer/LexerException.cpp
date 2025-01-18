#include "LexerException.h"

LexerException::LexerException(const std::string& msg, int lineNumber) : CompilerException(msg, lineNumber)
{}
