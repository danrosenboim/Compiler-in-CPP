#pragma once
#include "StatementNode.h"
#include "ForStatementNode.h"

class IfStatementNode : public StatementNode
{
public:
	IfStatementNode(int lineNumber);

	// Setters
	void setCondition(std::shared_ptr<ExpressionNode> condition);
	void setBody(std::shared_ptr<BlockNode> body);
	void setElseBlock(std::shared_ptr<BlockNode> elseBlock);

	// Getters
	std::shared_ptr<ExpressionNode> getCondition() const;
	std::shared_ptr<BlockNode> getBody() const;
	std::shared_ptr<BlockNode> getElseBlock() const;

	// StatementType
	virtual StatementType getStatementType() const override;

private:
	std::shared_ptr<ExpressionNode> condition;
	std::shared_ptr<BlockNode> body;
	std::shared_ptr<BlockNode> elseBlock;
	
};
