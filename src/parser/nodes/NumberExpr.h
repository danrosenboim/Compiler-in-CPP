#pragma once
#include "ExpressionNode.h"

class NumberExpr : public ExpressionNode
{
public:
	NumberExpr(int lineNumber, int value);

private:
	int value;
};
