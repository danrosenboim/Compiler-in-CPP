#pragma once
#include "ExpressionNode.h"
#include "IfStatementNode.h"

class ReturnStatement : public StatementNode
{
public:
	ReturnStatement(std::unique_ptr<ExpressionNode> expression);

private:
	std::unique_ptr<ExpressionNode> expression;
}
