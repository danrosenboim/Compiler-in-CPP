#include "StringExpr.h"

StringExpr::StringExpr(int lineNumber, const std::string& value) : ExpressionNode(lineNumber), value(value) {}

std::string StringExpr::getValue() const
{
    return value;
}

ExpressionType StringExpr::getExpressionVariant() const
{
    return ExpressionType::STRING;
}
