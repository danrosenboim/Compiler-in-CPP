#pragma once
#include "ParserException.h"

class ParserUnexpected : public ParserException
{
public:
	ParserUnexpected(const std::string& got, const std::string& expected, int lineNumber);

}
