#pragma once
#include "ExpressionNode.h"
#include "IfStatementNode.h"

class ReturnStatementNode : public StatementNode
{
public:
	ReturnStatementNode(int lineNumber);

	void setExpression(std::shared_ptr<ExpressionNode> expression);

private:
	std::shared_ptr<ExpressionNode> expression;
};
