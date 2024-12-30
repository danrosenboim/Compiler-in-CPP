#pragma once
#include "Node.h"

class ExpressionNode : public Node
{
public:
	ExpressionNode(int lineNumber);
	virtual ~ExpressionNode() = default;

	// Will be used in the semantic analyzer face
	void markForConversion(TypeKind target);

	void setCurrentType(TypeKind actual);

private:
	TypeKind expressionType;
	TypeKind targetType;
	bool needsConversion;

};
