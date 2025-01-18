#pragma once
#include "ExpressionNode.h"

class RealExpr : public ExpressionNode
{
public:
	RealExpr(int lineNumber, float value);

	// Getter
	float getValue() const;

	// Expression variant
	virtual ExpressionType getExpressionVariant() const override;

private:
	float value;

};
