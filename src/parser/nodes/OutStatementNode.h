#pragma once
#include "StatementNode.h"
#include "ExpressionNode.h"

class OutStatementNode : public StatementNode
{
public:
	OutStatementNode(int lineNumber);

	// Setter
	void setExpression(std::shared_ptr<ExpressionNode> expression);

	// Getter
	std::shared_ptr<ExpressionNode> getExpression() const;

	// StatementType
	virtual StatementType getStatementType() const override;

private:
	std::shared_ptr<ExpressionNode> expression;

};
