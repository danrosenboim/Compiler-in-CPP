#include "SymbolTable.h"

SymbolTable::SymbolTable() : scopesEntered(-1)
{ }

void SymbolTable::enterScope()
{
	++scopesEntered;
	symbolTableStack.emplace_back();
}

std::unordered_map<std::string, std::shared_ptr<Symbol>> SymbolTable::exitScope()
{
	--scopesEntered;
	// Return the latest element
	return symbolTableStack.pop_back();
}

int SymbolTable::getScopeLevel() const
{
	return scopesEntered;
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

int SymbolTable::getLatestSize() const
{
	int size = 0;
	// Loop through the vector backwards
	for (const auto& elem : symbolTableStack.back())
	{
		if (elem.second->functionNode == nullptr)
		{
			size++;
		}
	}

	return size;
}

