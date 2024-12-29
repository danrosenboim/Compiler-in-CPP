#pragma once
#include "ExpressionNode.h"

class IdentifierExpr : public ExpressionNode
{
public:
	IdentifierExpr(int lineNumber, const std::string& name);

private:
	std::string name;
};
