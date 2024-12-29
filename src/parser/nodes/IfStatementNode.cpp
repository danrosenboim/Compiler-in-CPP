#include "IfStatementNode.h"

IfStatementNode::IfStatementNode(int lineNumber) : StatementNode(lineNumber), condition(nullptr), body(nullptr), elseBlock(nullptr)
{
}

void IfStatementNode::setCondition(std::unique_ptr<ExpressionNode> condition)
{
	this->condition = std::move(condition);
}

void IfStatementNode::setBody(std::unique_ptr<BlockNode> body)
{
	this->body = std::move(body);
}

void IfStatementNode::setElseBlock(std::unique_ptr<BlockNode> elseBlock)
{
	this->elseBlock = std::move(elseBlock);
}

std::unique_ptr<ExpressionNode> condition;
std::unique_ptr<BlockNode> body;
std::unique_ptr<BlockNode> elseBlock;