#include "CodeGenCantOpenOutputFile.h"

CodeGenCantOutputOpenOutputFile::CodeGenCantOutputOpenOutputFile(std::string fileName) : CodeGenerationException(fileName, 0)
{
}
