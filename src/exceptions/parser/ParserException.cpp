#include "ParserException.h"

ParserException::ParserException(const std::string& msg, int lineNumber) : CompilerException(msg, lineNumber);
{}
