#include "ReturnStatementNode.h"

ReturnStatementNode::ReturnStatementNode(int lineNumber) : StatementNode(lineNumber)
{
}

void ReturnStatementNode::setExpression(std::shared_ptr<ExpressionNode> expression)
{
	this->expression = std::move(expression);
}

std::shared_ptr<ExpressionNode> ReturnStatementNode::getExpression() const
{
	return expression;
}

StatementType ReturnStatementNode::getStatementType() const
{
	return StatementType::RETURN;
}
