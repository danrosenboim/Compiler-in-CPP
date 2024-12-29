#pragma once
#include "ExpressionNode.h"

class IdentifierExpr : public ExpressionNode
{
public:
	IdentifierExpr(std::string name);

private:
	std::string name;
} 
