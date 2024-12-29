#include "ReturnStatementNode.h"

ReturnStatementNode::ReturnStatementNode(int lineNumber) : StatementNode(lineNumber)
{
}

void ReturnStatementNode::setExpression(std::unique_ptr<ExpressionNode> expression)
{
	this->expression = std::move(expression);
}
