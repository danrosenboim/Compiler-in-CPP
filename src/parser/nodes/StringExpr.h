#pragma once
#include "ExpressionNode.h"

class StringExpr : public ExpressionNode
{
public:
	StringExpr(int lineNumber, const std::string& value);
	
	// Getter
	std::string getValue() const;


	// Expression variant
	virtual ExpressionType getExpressionVariant() const override;

private:
	std::string value;
};