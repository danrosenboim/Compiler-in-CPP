#pragma once
#include "SymbolTable.h"
#include "../parser/nodes/ProgramNode.h"

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

	/*
	Function that analyzes the file and checks the types
	Inputs: the head output node
	Outputs: none
	*/
	void analyze(std::unique_ptr<ProgramNode> programNode);
	
private:
	// Symbol table to keep track of all the variables and functions
	std::unique_ptr<SymbolTable> symbolTable;

	/*
	This function registers a function
	Inputs: Function node
	Outputs: none
	*/
	void registerFunction(std::shared_ptr<FunctionNode> func);

};
