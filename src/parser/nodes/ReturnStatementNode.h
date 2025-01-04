#pragma once
#include "ExpressionNode.h"
#include "IfStatementNode.h"

class ReturnStatementNode : public StatementNode
{
public:
	ReturnStatementNode(int lineNumber);

	// Setter
	void setExpression(std::shared_ptr<ExpressionNode> expression);
	void setFunctionName(const std::string& functionName);

	// Getter
	std::shared_ptr<ExpressionNode> getExpression() const;
	std::string getFunctionName() const;

	// StatementType
	virtual StatementType getStatementType() const override;

private:
	std::shared_ptr<ExpressionNode> expression;
	std::string functionName;
};
