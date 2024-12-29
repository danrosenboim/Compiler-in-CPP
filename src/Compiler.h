#pragma once
#include <string>
#include "lexer/Lexer.h"
#include "parser/Parser.h"


class Compiler
{
public:
	Compiler(const std::string& filePath);

private:
	// The file path of the source code
	std::string m_filePath;

	// Compiler parts
	std::shared_ptr<Lexer> scanner;
	std::unique_ptr<Parser> parser;
};
