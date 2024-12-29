#pragma once
#include "ExpressionNode.h"
#include "ExpressionType.h"

class BinaryExpr : public ExpressionNode
{
public:
	BinaryExpr(int lineNumber);

	void setType(ExpressionType type);
	void setLeft(std::unique_ptr<ExpressionNode> left);
	void setRight(std::unique_ptr<ExpressionNode> right);

private:
	ExpressionType type;
	std::unique_ptr<ExpressionNode> left;
	std::unique_ptr<ExpressionNode> right;
};
