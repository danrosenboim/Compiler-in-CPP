#include "ForStatementNode.h"

ForStatementNode::ForStatementNode(int lineNumber) : StatementNode(lineNumber)
{
}

void ForStatementNode::setVariableName(std::string variableName)
{
	this->variableName = variableName;
}

void ForStatementNode::setInitExpr(std::shared_ptr<ExpressionNode> initExpr)
{
	this->initExpr = std::move(initExpr);
}

void ForStatementNode::setCondition(std::shared_ptr<ExpressionNode> condition)
{
	this->condition = std::move(condition);
}

void ForStatementNode::setBody(std::shared_ptr<BlockNode> body)
{
	this->body = std::move(body);
}
