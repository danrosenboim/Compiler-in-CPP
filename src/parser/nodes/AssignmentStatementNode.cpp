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

std::string AssignmentStatementNode::getIdentifier() const
{
	return identifier;
}

std::shared_ptr<ExpressionNode> AssignmentStatementNode::getExpression() const
{
	return expression;
}

StatementType AssignmentStatementNode::getStatementType() const
{
	return StatementType::ASSIGNMENT;
}
