#pragma once
#include "Node.h"
#include "TypeKind.h"
#include "ExpressionType.h"

class ExpressionNode : public Node
{
public:
	ExpressionNode(int lineNumber);
	virtual ~ExpressionNode() = default;

	// Will be used in the semantic analyzer face
	void markForConversion(TypeKind target);

	// Setters
	void setCurrentType(TypeKind actual);
	
	// Getters for each variable
	TypeKind getExpressionType() const;
	TypeKind getTargetType() const;
	bool getNeedsConversion() const;

	// Expression variant
	virtual ExpressionType getExpressionVariant() const;

private:
	TypeKind expressionType;
	TypeKind targetType;
	bool needsConversion;

};
