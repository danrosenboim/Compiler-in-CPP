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

std::shared_ptr<ExpressionNode> IfStatementNode::getCondition() const
{
	return condition;
}

std::shared_ptr<BlockNode> IfStatementNode::getBody() const
{
	return body;
}

std::shared_ptr<BlockNode> IfStatementNode::getElseBlock() const
{
	return elseBlock;
}

StatementType IfStatementNode::getStatementType() const
{
	return StatementType::IF;
}
