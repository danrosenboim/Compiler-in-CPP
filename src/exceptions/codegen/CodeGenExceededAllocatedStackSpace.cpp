#include "CodeGenExceededAllocatedStackSpace.h"

CodeGenExceededAllocatedStackSpace::CodeGenExceededAllocatedStackSpace() : CodeGenerationException("Cannot use more space than allocated in the Scope Manager", 0)
{
}
