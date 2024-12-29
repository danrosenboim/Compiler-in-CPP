#pragma once
#include "ExpressionNode.h"

class StringExpr : public ExpressionNode
{
public:
	StringExpr(std::string value);

private:
	std::string value;
} 
