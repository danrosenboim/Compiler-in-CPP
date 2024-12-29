#include "IdentifierExpr.h"

IdentifierExpr::IdentifierExpr(int lineNumber, const std::string& name) : ExpressionNode(lineNumber), name(name)
{}
