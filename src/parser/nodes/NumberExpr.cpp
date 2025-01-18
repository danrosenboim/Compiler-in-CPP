#include "NumberExpr.h"


NumberExpr::NumberExpr(int lineNumber, int value) : ExpressionNode(lineNumber), value(value)
{
}

int NumberExpr::getValue() const
{
    return value;
}

ExpressionType NumberExpr::getExpressionVariant() const
{
    return ExpressionType::NUMBER;
}
