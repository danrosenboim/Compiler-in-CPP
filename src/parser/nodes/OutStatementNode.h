#pragma once
#include "StatementNode.h"
#include "ExpressionNode.h"

class OutStatementNode : public StatementNode
{
public:
	OutStatemenntNode(std::unique_ptr<ExpressionNode> expression);

private:
	std::unique_ptr<ExpressionNode> expression;
}
