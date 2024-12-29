#include "BinaryExpr.h"

BinaryExpr::BinaryExpr(int lineNumber) : ExpressionNode(lineNumber)
{
}

void BinaryExpr::setType(ExpressionType type)
{
	this->type = type;
}

void BinaryExpr::setLeft(std::unique_ptr<ExpressionNode> left)
{
	this->left = std::move(left);
}

void BinaryExpr::setRight(std::unique_ptr<ExpressionNode> right)
{
	this->right = std::move(right);
}

