#include "NotExpr.h"

NotExpr::NotExpr(int lineNumber) : ExpressionNode(lineNumber)
{}

void NotExpr::setExpression(std::shared_ptr<ExpressionNode> expression)
{
	this->expression = std::move(expression);
}
