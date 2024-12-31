#pragma once
#include "ExpressionNode.h"
#include "BinaryExprType.h"

class BinaryExpr : public ExpressionNode
{
public:
	BinaryExpr(int lineNumber);

	// Setters
	void setType(BinaryExprType type);
	void setLeft(std::shared_ptr<ExpressionNode> left);
	void setRight(std::shared_ptr<ExpressionNode> right);

	// Getters
	BinaryExprType getType() const;
	std::shared_ptr<ExpressionNode> getLeft() const;
	std::shared_ptr<ExpressionNode> getRight() const;

	// Expression variant
	virtual ExpressionType getExpressionVariant() const override;

private:
	BinaryExprType type;
	std::shared_ptr<ExpressionNode> left;
	std::shared_ptr<ExpressionNode> right;
};
