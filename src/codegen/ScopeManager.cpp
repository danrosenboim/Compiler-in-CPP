#include "ScopeManager.h"

ScopeManager::ScopeManager() : currentScopeLevel(0)
{
    // Initialize global scope
    scopeChain.push_back({
        0,      // scopeLevel
        0,      // currentOffset
        0,      // allocatedSize
        {}      // variables
    });
}

void ScopeManager::enterScope(int size)
{
    currentScopeLevel++;

    scopeChain.push_back({
        currentScopeLevel,
        0,          // Start at 0 and go downward
        size,       // Track allocated size
        {}
    });
}

void ScopeManager::exitScope()
{
    if (!scopeChain.empty())
    {
        scopeChain.pop_back();
        currentScopeLevel--;
    }
}

int ScopeManager::addVariable(const std::string& varName)
{
    if (scopeChain.empty())
    {
        throw CodeGenCannotLeaveGlobalSpace();
    }

    auto& currentScope = scopeChain.back();
    currentScope.currentOffset -= 8; // Go down by 8 bytes

    // Check if we exceeded allocated space
    if (-currentScope.currentOffset > currentScope.allocatedSize)
    {
        throw CodeGenExceededAllocatedStackSpace();
    }

    currentScope.variables[varName] = currentScope.currentOffset;
    return currentScope.currentOffset;
}

void ScopeManager::addVariableWithOffset(const std::string& varName, int manualOffset)
{
    if (scopeChain.empty())
    {
        throw CodeGenCannotLeaveGlobalSpace();
    }
    scopeChain.back().variables[varName] = manualOffset;
}

std::pair<int, int> ScopeManager::getVariableOffset(const std::string& varName)
{
    // Search from innermost to outermost scope
    for (auto it = scopeChain.rbegin(); it != scopeChain.rend(); ++it)
    {
        auto varIt = it->variables.find(varName);
        if (varIt != it->variables.end())
        {
            // Return scope level difference and offset
            int levelDiff = currentScopeLevel - it->scopeLevel;
            return { levelDiff, varIt->second };
        }
    }

    // Not found in any scope, must be global
    return { -1, 0 };
}

int ScopeManager::getCurrentScopeLevel() const
{
    return currentScopeLevel;
}
