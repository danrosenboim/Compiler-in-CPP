#include "SymbolTable.h"

SymbolTable::SymbolTable() : ordinalPos(0)
{
	// First element for global scope
	symbolTableStack.resize(1);
}

void SymbolTable::enterScope()
{
	++ordinalPos;
	// Resize the vector, so it will initialize the needed maps
	symbolTableStack.resize(ordinalPos + 1);
}

void SymbolTable::exitScope()
{
	ordinalPos--;
	// Remove the latest element
	symbolTableStack.pop_back();
}

int SymbolTable::getScopeLevel() const
{
	return ordinalPos;
}


void SymbolTable::addEntryToLatest(const Symbol& symbol)
{
	symbolTableStack.back()[symbol.varName] = std::make_unique<Symbol>(symbol);
}

Symbol* SymbolTable::tableLookup(const std::string& name) const
{
	// Loop through the vector backwards
	for(auto elem = symbolTableStack.rbegin(); it != symbolTableStack.rend(); ++it)
	{
		auto it = elem->find(name);
		if(it != elem->end())
		{
			return it->second.get();
		}
	}
	return nullptr;
}

Symbol* SymbolTable::currentScopeLookup(const std::string& name) const
{
	auto it = symbolTableStack.back().find(name);
	if(it != symbolTableStack.back().end())
	{
		return it->second.get();
	}

	return nullptr;
}

