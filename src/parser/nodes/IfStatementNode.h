#pragma once
#include "StatementNode.h"
#include "ForStatementNode.h"

class IfStatementNode : public StatementNode
{
public:
	IfStatementNode(int lineNumber);

	void setCondition(std::shared_ptr<ExpressionNode> condition);
	void setBody(std::shared_ptr<BlockNode> body);
	void setElseBlock(std::shared_ptr<BlockNode> elseBlock);

private:
	std::shared_ptr<ExpressionNode> condition;
	std::shared_ptr<BlockNode> body;
	std::shared_ptr<BlockNode> elseBlock;
	
};
