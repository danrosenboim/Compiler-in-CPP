#include <iostream>
#include "Compiler.h"

int main()
{	
	try
	{
		std::string filePath = "testing2.dan";
		std::string outputPath = "output.s";

		// Run the compiler with the source code file
		Compiler compiler(filePath, outputPath);

		compiler.run();

		return 0;
	}
	catch (const CompilerException& e)
	{
		std::cerr << "Compilation failed: " << e.what() << std::endl;
		return 1;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Unexpected error: " << e.what() << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cerr << "Unknown error occurred" << std::endl;
		return 1;
	}
}
