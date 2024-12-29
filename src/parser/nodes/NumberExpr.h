#pragma once
#include "ExpressionNode.h"

class NumberExpr : public ExpressionNode
{
public:
	NumberExpr(int value);

private:
	int value;
};
