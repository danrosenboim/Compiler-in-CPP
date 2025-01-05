#include "CodeGenExceededAllocatedStackSpace.h"

CodeGenExceededAllocatedStackSpace::CodeGenExceededAllocatedStackSpace() : CodeGenerationException("Cannot use more space than allocated in the stack", 0)
{
}
