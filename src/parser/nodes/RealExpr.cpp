#include "RealExpr.h"

RealExpr::RealExpr(int lineNumber, float value) : ExpressionNode(lineNumber), value(value) {}

ExpressionType RealExpr::getExpressionVariant() const
{
    return ExpressionType::REAL;
}
