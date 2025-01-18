#pragma once
#include "CodeGenerationException.h"

class CodeGenCannotLeaveGlobalSpace : public CodeGenerationException
{
public:
	CodeGenCannotLeaveGlobalSpace();
};