#pragma once
#include <string>
#include <memory>
#include "../parser/nodes/TypeKind.h"
#include "../parser/nodes/FunctionNode.h"
#include "../parser/nodes/DeclarationStatementNode.h"

enum class SymbolType
{
	// Possible types of symbols
	PARAM, LOCAL, GLOBAL
};

// SymbolTable entry
class Symbol
{
public:
	Symbol();
	Symbol(SymbolType type, TypeKind varType, std::string varName, int ordinalPos);

	SymbolType type;
	TypeKind varType;
	std::string varName;
	int ordinalPos;
	std::shared_ptr<FunctionNode> functionNode;
	std::shared_ptr<DeclarationStatementNode> declarationNode;

};
