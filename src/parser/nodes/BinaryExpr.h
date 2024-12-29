#pragma once
#include "ExpressionNode.h"

class BinaryExpr : public ExpressionNode
{
public:
	BinaryExpr(ExpressionType type, std::unique_ptr<ExpressionNode> left, std::unique_ptr<ExpressionNode> right);

private:
	ExpressionType type;
	std::unique_ptr<ExpressionNode> left;
	std::unique_ptr<ExpressionNode> right;
}
