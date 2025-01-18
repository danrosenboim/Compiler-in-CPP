#include "BinaryExpr.h"

BinaryExpr::BinaryExpr(int lineNumber) : ExpressionNode(lineNumber)
{
}

void BinaryExpr::setType(BinaryExprType type)
{
	this->type = type;
}

void BinaryExpr::setLeft(std::shared_ptr<ExpressionNode> left)
{
	this->left = std::move(left);
}

void BinaryExpr::setRight(std::shared_ptr<ExpressionNode> right)
{
	this->right = std::move(right);
}

BinaryExprType BinaryExpr::getType() const
{
	return type;
}

std::shared_ptr<ExpressionNode> BinaryExpr::getLeft() const
{
	return left;
}

std::shared_ptr<ExpressionNode> BinaryExpr::getRight() const
{
	return right;
}

ExpressionType BinaryExpr::getExpressionVariant() const
{
	return ExpressionType::BINARY;
}

