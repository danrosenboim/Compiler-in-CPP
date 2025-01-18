#pragma once
#include <string>
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "analyzer/Analyzer.h"
#include "codegen/CodeGeneration.h"


class Compiler
{
public:
	Compiler(const std::string& filePath, const std::string& outputPath);
	void run();

private:
	// The file path of the source code
	std::string m_filePath;

	// The output file path
	std::string m_outputPath;

	// Compiler parts
	std::shared_ptr<Lexer> scanner;
	std::unique_ptr<Parser> parser;
	std::unique_ptr<Analyzer> analyzer;
	std::unique_ptr<CodeGeneration> codeGen;
};
