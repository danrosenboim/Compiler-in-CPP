#pragma once
#include "ExpressionNode.h"

class BoolExpr : public ExpressionNode
{
public:
	BoolExpr(int lineNumber, bool value);

	// Expression variant
	virtual ExpressionType getExpressionVariant() const override;
private:
	bool value;
};
