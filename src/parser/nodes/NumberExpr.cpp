#include "NumberExpr.h"


NumberExpr::NumberExpr(int lineNumber, int value) : ExpressionNode(lineNumber), value(value)
{
}

ExpressionType NumberExpr::getExpressionVariant() const
{
    return ExpressionType::NUMBER;
}
