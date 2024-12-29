#pragma once
#include "ExpressionNode.h"

class RealExpr : public ExpressionNode
{
public:
	RealExpr(float value);

private:
	float value;

};
