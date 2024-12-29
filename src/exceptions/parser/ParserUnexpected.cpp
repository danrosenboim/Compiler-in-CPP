#include "ParserUnexpected.h"

ParserUnexpected::ParserUnexpected(const std::string& got, const std::string& expected, int lineNumber) : ParserException("Expected '" + expected + "', got '" + got + "'.", lineNumber) {}
