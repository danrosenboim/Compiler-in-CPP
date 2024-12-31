#include "IdentifierExpr.h"

IdentifierExpr::IdentifierExpr(int lineNumber, const std::string& name) : ExpressionNode(lineNumber), name(name)
{}

std::string IdentifierExpr::getName() const
{
    return name;
}

ExpressionType IdentifierExpr::getExpressionVariant() const
{
    return ExpressionType::IDENTIFIER;
}
