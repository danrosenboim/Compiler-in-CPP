#pragma once
#include "ExpressionNode.h"

class NumberExpr : public ExpressionNode
{
public:
	NumberExpr(int lineNumber, int value);

	// Expression variant
	virtual ExpressionType getExpressionVariant() const override;

private:
	int value;
};
