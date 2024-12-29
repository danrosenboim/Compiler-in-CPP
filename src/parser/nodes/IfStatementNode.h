#pragma once
#include "StatementNode.h"
#include "ForStatementNode.h"

class IfStatementNode : public StatementNode
{
public:
	IfStatementNode(std::unique_ptr<ExpressionNode> condition, std::unique_ptr<BlockNode> body, std::unique_ptr<BlockNode> elseBlock);

private:
	std::unique_ptr<ExpressionNode> condition;
	std::unique_ptr<BlockNode> body;
	std::unique_ptr<BlockNode> elseBlock;
	
};
