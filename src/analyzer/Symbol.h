#pragma once
#include <string>
#include "../parser/nodes/TypeKind.h"

enum class SymbolType
{
	// Possible types of symbols
	PARAM, LOCAL, GLOBAL
};

// SymbolTable entry
struct Symbol
{
	Symbol();
	Symbol(SymbolType type, TypeKind varType, std::string varName, int ordinalPos);

	SymbolType type;
	TypeKind varType;
	std::string varName;
	int ordinalPos;

};
