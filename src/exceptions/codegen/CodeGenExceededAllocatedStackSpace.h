#pragma once
#include "CodeGenerationException.h"

class CodeGenExceededAllocatedStackSpace : public CodeGenerationException
{
public:
	CodeGenExceededAllocatedStackSpace();
};