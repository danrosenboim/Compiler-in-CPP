#include "Symbol.h"

Symbol::Symbol() : type(SymbolType::GLOBAL), varType(TypeKind::NUM), varName(""), ordinalPos(0), functionNode(nullptr), declarationNode(nullptr) {}

Symbol::Symbol(SymbolType type, TypeKind varType, std::string varName, int ordinalPos) : type(type), varType(varType), varName(varName), ordinalPos(ordinalPos), functionNode(nullptr), declarationNode(nullptr) {}
