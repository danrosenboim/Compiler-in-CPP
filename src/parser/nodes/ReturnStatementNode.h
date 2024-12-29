#pragma once
#include "ExpressionNode.h"
#include "IfStatementNode.h"

class ReturnStatementNode : public StatementNode
{
public:
	ReturnStatementNode(int lineNumber);

	void setExpression(std::unique_ptr<ExpressionNode> expression);

private:
	std::unique_ptr<ExpressionNode> expression;
};
