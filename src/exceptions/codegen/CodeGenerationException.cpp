#include "CodeGenerationException.h"

CodeGenerationException::CodeGenerationException(const std::string& msg, int lineNumber) : CompilerException(msg, lineNumber)
{
}