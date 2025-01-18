#include "ReturnStatementNode.h"

ReturnStatementNode::ReturnStatementNode(int lineNumber) : StatementNode(lineNumber)
{
}

void ReturnStatementNode::setExpression(std::shared_ptr<ExpressionNode> expression)
{
	this->expression = std::move(expression);
}

void ReturnStatementNode::setFunctionName(const std::string& functionName)
{
	this->functionName = functionName;
}

std::shared_ptr<ExpressionNode> ReturnStatementNode::getExpression() const
{
	return expression;
}

std::string ReturnStatementNode::getFunctionName() const
{
	return functionName;
}

StatementType ReturnStatementNode::getStatementType() const
{
	return StatementType::RETURN;
}
