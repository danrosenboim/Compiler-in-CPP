#include "Compiler.h"

Compiler::Compiler(const std::string& filePath, const std::string& outputPath) : m_filePath(filePath), m_outputPath(outputPath), scanner(std::make_shared<Lexer>(filePath)), parser(std::make_unique<Parser>(scanner)), analyzer(std::make_unique<Analyzer>()), codeGen(std::make_unique<CodeGeneration>(filePath, outputPath))
{ }


void Compiler::run()
{
	// Error handling
	try
	{
		std::shared_ptr<ProgramNode> programAST = parser->parseProgram();
		analyzer->analyze(programAST);

		std::cout << "Compiler analyzation complete." << std::endl;

		codeGen->generate(programAST);
		std::cout << "Output finished" << std::endl;
	}
	catch (const CompilerException& e)
    {
        std::cerr << e.what() << std::endl;
        throw; // Rethrow to maintain the exception chain
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        throw;
    }
    catch (...)
    {
        std::cerr << "Unknown error occurred" << std::endl;
        throw;
    }
}

