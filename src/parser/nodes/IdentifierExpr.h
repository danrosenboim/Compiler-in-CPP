#pragma once
#include "ExpressionNode.h"

class IdentifierExpr : public ExpressionNode
{
public:
	IdentifierExpr(int lineNumber, const std::string& name);

	// Getters
	std::string getName() const;

	// Expression variant
	virtual ExpressionType getExpressionVariant() const override;

private:
	std::string name;
};
