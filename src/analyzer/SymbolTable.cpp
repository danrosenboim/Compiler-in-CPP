#include "SymbolTable.h"

SymbolTable::SymbolTable() : ordinalPos(0)
{
	// First element for global scope
	symbolTableStack.emplace_back();
}

void SymbolTable::enterScope()
{
	++ordinalPos;
	symbolTableStack.emplace_back();
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
	symbolTableStack.back()[symbol.varName] = std::make_shared<Symbol>(symbol);
}

std::shared_ptr<Symbol> SymbolTable::tableLookup(const std::string& name) const
{
	// Loop through the vector backwards
	for(auto elem = symbolTableStack.rbegin(); elem != symbolTableStack.rend(); ++elem)
	{
		auto it = elem->find(name);
		if(it != elem->end())
		{
			return it->second;
		}
	}

	return nullptr;
}

std::shared_ptr<Symbol> SymbolTable::currentScopeLookup(const std::string& name) const
{
	auto it = symbolTableStack.back().find(name);
	if(it != symbolTableStack.back().end())
	{
		return it->second;
	}

	return nullptr;
}

