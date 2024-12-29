#pragma once
#include "StatementNode.h"
#include "ExpressionNode.h"

class OutStatementNode : public StatementNode
{
public:
	OutStatementNode(int lineNumber);

	void setExpression(std::unique_ptr<ExpressionNode> expression);

private:
	std::unique_ptr<ExpressionNode> expression;

};
