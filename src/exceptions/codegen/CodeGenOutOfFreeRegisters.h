#pragma once
#include "CodeGenerationException.h"

class CodeGenOutOfFreeRegisters : public CodeGenerationException
{
public:
	CodeGenOutOfFreeRegisters();
};