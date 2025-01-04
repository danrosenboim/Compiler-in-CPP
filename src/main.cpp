#include <iostream>
#include "Compiler.h"

int main()
{
	std::string filePath = "testing.dan";
	std::string outputPath = "output.s";

	// Run the compiler with the source code file
	Compiler compiler(filePath, outputPath);

	compiler.run();

	return 0;
}
