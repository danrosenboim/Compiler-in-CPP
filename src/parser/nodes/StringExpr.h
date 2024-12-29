#pragma once
#include "ExpressionNode.h"

class StringExpr : public ExpressionNode
{
public:
	StringExpr(int lineNumber, const std::string& value);

private:
	std::string value;
};