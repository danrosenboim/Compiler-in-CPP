#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "../exceptions/codegen/CodeGenCannotLeaveGlobalSpace.h"
#include "../exceptions/codegen/CodeGenExceededAllocatedStackSpace.h"

class ScopeManager {
public:
    ScopeManager();

    /*
     * Creates a new scope with pre-allocated stack size
     * Inputs: size - total size to allocate for this scope's variables
     * Outputs: none
     */
    void enterScope(int size);

    /*
     * Exits current scope
     * Inputs: none
     * Outputs: none
     */
    void exitScope();

    /*
     * Adds a variable to current scope's tracking (doesn't allocate space)
     * Inputs: variable name
     * Outputs: offset assigned to the variable
     */
    int addVariable(const std::string& varName);

    /*
     * Adds a variable to current scope's tracking with a manual offset
     * Inputs: variable name
     * Outputs: void
     */
    void addVariableWithOffset(const std::string& varName, int manualOffset);

    /*
     * Gets the offset and scope level difference for a variable
     * Inputs: variable name
     * Outputs: pair of {scope level difference, offset}. -1 level means global
     */
    std::pair<int, int> getVariableOffset(const std::string& varName);

    /*
    Returns current scope level
    Inputs: none
    Outputs: current scope level
    */
    int getCurrentScopeLevel() const;

private:
    struct ScopeFrame {
        int scopeLevel;          // Current scope depth
        int currentOffset;       // Next available offset for variables
        int allocatedSize;       // Size allocated for the stack
        std::unordered_map<std::string, int> variables;  // Variable to offset mapping
    };

    std::vector<ScopeFrame> scopeChain;
    int currentScopeLevel;
};