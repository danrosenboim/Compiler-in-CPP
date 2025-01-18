#pragma once
#include "ExpressionNode.h"

class BoolExpr : public ExpressionNode
{
public:
	BoolExpr(int lineNumber, bool value);

	// Getter
	bool getValue() const;

	// Expression variant
	virtual ExpressionType getExpressionVariant() const override;
private:
	bool value;
};
