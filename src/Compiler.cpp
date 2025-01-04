#include "Compiler.h"

Compiler::Compiler(const std::string& filePath, const std::string& outputPath) : m_filePath(filePath), m_outputPath(outputPath), scanner(std::make_shared<Lexer>(filePath)), parser(std::make_unique<Parser>(scanner)), analyzer(std::make_unique<Analyzer>()), codeGen(std::make_unique<CodeGeneration>(filePath, outputPath))
{ }


void Compiler::run()
{
	// Error handling
	try
	{
		std::unique_ptr<ProgramNode> programAST = parser->parseProgram();
		programAST = analyzer->analyze(std::move(programAST));

		std::cout << "Compiler analyzation complete." << std::endl;

		codeGen->generate(std::move(programAST));
		std::cout << "Output finished" << std::endl;
	}
	catch (const CompilerException& e)
	{
		std::cout << e.what() << std::endl;
	}
}

