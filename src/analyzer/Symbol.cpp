#include "Symbol.h"

Symbol::Symbol() : type(SymbolType::GLOBAL), varType(TypeKind::INT), varName(""), ordinalPos(0) {}

Symbol::Symbol(SymbolType type, TypeKind varType, std::string varName, int ordinalPos) : type(type), varType(varType), varName(varName), ordinalPos(ordinalPos) {}


