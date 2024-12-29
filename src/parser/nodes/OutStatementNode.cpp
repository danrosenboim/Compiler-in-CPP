#include "OutStatementNode.h"


OutStatementNode::OutStatementNode(int lineNumber) : StatementNode(lineNumber)
{
}

void OutStatementNode::setExpression(std::unique_ptr<ExpressionNode> expression)
{
	this->expression = std::move(expression);
}
