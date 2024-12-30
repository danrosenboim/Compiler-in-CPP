#include "AssignmentStatementNode.h"


AssignmentStatementNode::AssignmentStatementNode(int lineNumber) : StatementNode(lineNumber)
{
}

void AssignmentStatementNode::setIdentifier(std::string id)
{
	this->identifier = id;
}

void AssignmentStatementNode::setExpression(std::shared_ptr<ExpressionNode> expression)
{
	this->expression = std::move(expression);
}
