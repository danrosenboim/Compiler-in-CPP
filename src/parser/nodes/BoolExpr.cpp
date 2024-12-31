#include "BoolExpr.h"

BoolExpr::BoolExpr(int lineNumber, bool value) : ExpressionNode(lineNumber), value(value)
{
}

ExpressionType BoolExpr::getExpressionVariant() const
{
    return ExpressionType::BOOL;
}
