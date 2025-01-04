#include "CodeGenOutOfFreeRegisters.h"

CodeGenOutOfFreeRegisters::CodeGenOutOfFreeRegisters() : CodeGenerationException("No free registers available.", 0)
{
}
