#pragma once
#include "ExpressionNode.h"

class RealExpr : public ExpressionNode
{
public:
	RealExpr(int lineNumber, float value);

private:
	float value;

};
