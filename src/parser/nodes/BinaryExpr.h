#pragma once
#include "ExpressionNode.h"
#include "ExpressionType.h"

class BinaryExpr : public ExpressionNode
{
public:
	BinaryExpr(int lineNumber);

	void setType(ExpressionType type);
	void setLeft(std::shared_ptr<ExpressionNode> left);
	void setRight(std::shared_ptr<ExpressionNode> right);

private:
	ExpressionType type;
	std::shared_ptr<ExpressionNode> left;
	std::shared_ptr<ExpressionNode> right;
};
