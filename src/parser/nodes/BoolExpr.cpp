#include "BoolExpr.h"

BoolExpr::BoolExpr(int lineNumber, bool value) : ExpressionNode(lineNumber), value(value)
{
}

bool BoolExpr::getValue() const
{
    return value;
}

ExpressionType BoolExpr::getExpressionVariant() const
{
    return ExpressionType::BOOL;
}
