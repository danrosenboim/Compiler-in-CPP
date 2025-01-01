#pragma once
#include "ExpressionNode.h"

class NumberExpr : public ExpressionNode
{
public:
	NumberExpr(int lineNumber, int value);

	// Getter
	int getValue() const;

	// Expression variant
	virtual ExpressionType getExpressionVariant() const override;

private:
	int value;
};
