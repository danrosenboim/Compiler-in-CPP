#pragma once
#include "ExpressionNode.h"
#include "IfStatementNode.h"

class ReturnStatementNode : public StatementNode
{
public:
	ReturnStatementNode(int lineNumber);

	// Setter
	void setExpression(std::shared_ptr<ExpressionNode> expression);

	// Getter
	std::shared_ptr<ExpressionNode> getExpression() const;

	// StatementType
	virtual StatementType getStatementType() const override;

private:
	std::shared_ptr<ExpressionNode> expression;
};
