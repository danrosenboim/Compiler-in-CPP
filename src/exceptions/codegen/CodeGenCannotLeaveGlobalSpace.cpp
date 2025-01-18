#include "CodeGenCannotLeaveGlobalSpace.h"

CodeGenCannotLeaveGlobalSpace::CodeGenCannotLeaveGlobalSpace() : CodeGenerationException("Cannot leave the global scope, in the Scope Manager", 0)
{
}
