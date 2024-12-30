#pragma once
#include "ExpressionNode.h"

class RealExpr : public ExpressionNode
{
public:
	RealExpr(int lineNumber, float value);

	// Expression variant
	virtual ExpressionType getExpressionVariant() const override;

private:
	float value;

};
