#include "OutStatementNode.h"


OutStatementNode::OutStatementNode(int lineNumber) : StatementNode(lineNumber)
{
}

void OutStatementNode::setExpression(std::shared_ptr<ExpressionNode> expression)
{
	this->expression = std::move(expression);
}

std::shared_ptr<ExpressionNode> OutStatementNode::getExpression() const
{
	return expression;
}

StatementType OutStatementNode::getStatementType() const
{
	return StatementType::OUT;
}
