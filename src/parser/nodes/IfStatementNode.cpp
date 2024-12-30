#include "IfStatementNode.h"

IfStatementNode::IfStatementNode(int lineNumber) : StatementNode(lineNumber), condition(nullptr), body(nullptr), elseBlock(nullptr)
{
}

void IfStatementNode::setCondition(std::shared_ptr<ExpressionNode> condition)
{
	this->condition = std::move(condition);
}

void IfStatementNode::setBody(std::shared_ptr<BlockNode> body)
{
	this->body = std::move(body);
}

void IfStatementNode::setElseBlock(std::shared_ptr<BlockNode> elseBlock)
{
	this->elseBlock = std::move(elseBlock);
}
