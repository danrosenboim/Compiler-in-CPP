#include "RealExpr.h"

RealExpr::RealExpr(int lineNumber, float value) : ExpressionNode(lineNumber), value(value) {}

float RealExpr::getValue() const
{
    return value;
}

ExpressionType RealExpr::getExpressionVariant() const
{
    return ExpressionType::REAL;
}
