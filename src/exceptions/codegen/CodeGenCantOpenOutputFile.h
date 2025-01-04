#pragma once
#include "CodeGenerationException.h"

class CodeGenCantOutputOpenOutputFile : public CodeGenerationException
{
public:
	CodeGenCantOutputOpenOutputFile(std::string fileName);
};