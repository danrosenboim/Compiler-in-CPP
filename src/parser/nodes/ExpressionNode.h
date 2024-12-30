#pragma once
#include "Node.h"
#include "TypeKind.h"

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

private:
	TypeKind expressionType;
	TypeKind targetType;
	bool needsConversion;

};
