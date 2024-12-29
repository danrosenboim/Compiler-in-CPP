#pragma once
#include "ExpressionNode.h"

class BoolExpr : public ExpressionNode
{
public:
	BoolExpr(int lineNumber, bool value);

private:
	bool value;
};
