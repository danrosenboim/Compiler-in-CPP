#pragma once
#include <vector>
#include <string>
#include "Symbol.h"

class SymbolTable
{
public:
	SymbolTable();

	/*
	Pushes a new map into the symbol table stack
	Inputs: none
	Outputs: none
	*/
	void enterScope();

	/*
	Pops the latest map off of the symbol table stack
	Inputs: none
	Outputs: none
	*/
	void exitScope();

	/*
	Gets the currennt ordinal position
	Inputs: none
	Outputs: none
	*/
	int getScopeLevel() const;
	
	/*
	Adds an entry to the latest map in the symbol stack refering to the current scope
	Inputs: the symbol you want to add
	Outputs: none
	*/
	void addEntryToLatest(const Symbol& symbol);

	/*
	Searches the symbol table and returns the symbol if found
	Inputs: the name of the variable
	Outputs: returns the symbol
	*/
	Symbol* tableLookup(const std::string& name) const;

	/*
	Looksup in the current scope, this function will help us find redefinitions of the same variable
	Input: name of the variable to search for
	Outputs: returns the symbol if found*/
	Symbol* currentScopeLookup(const std::string& name) const;

private:
	// Using a stack to express all the blocks, the latest item in the stack is the
	// latest block with all of the variables defined in it
	std::vector<std::map<std::string, std::unique_ptr<Symbol>>> symbolTableStack;

	// The number of scopes entered, 0 being GLOBAL
	int ordinalPos;
};

