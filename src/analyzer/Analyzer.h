#pragma once
#include "SymbolTable.h"

class Analyzer
{
public:
	Analyzer();

	/*
	 * Checks if one type can convert to the other
	 * Inputs: from, to, types to check
	 * Outputs: bool, return true or false if you can convert from one type to the other
	 * */
	static bool canConvert(TypeKind from, TypeKind to);

	
private:
	std::unique_ptr<SymbolTable> symbolTable;
};
