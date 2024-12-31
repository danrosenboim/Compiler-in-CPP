#include "Compiler.h"

Compiler::Compiler(const std::string& filePath) : m_filePath(filePath), scanner(std::make_shared<Lexer>(filePath)), parser(std::make_unique<Parser>(scanner)), analyzer(std::make_unique<Analyzer>())
{ }


void Compiler::run()
{
	// Error handling
	try
	{
		std::unique_ptr<ProgramNode> programAST = parser->parseProgram();
		analyzer->analyze(std::move(programAST));

		std::cout << "Compiler analyzation complete." << std::endl;
	}
	catch (const CompilerException& e)
	{
		std::cout << e.what() << std::endl;
	}
}

