#include <iostream>
#include "Compiler.h"

int main()
{
	std::string filePath = "testing.dan";

	// Run the compiler with the source code file
	Compiler compiler(filePath);

	compiler.run();

	return 0;
}
