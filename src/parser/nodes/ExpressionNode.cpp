#include "ExpressionNode.h"

ExpressionNode::ExpressionNode(int lineNumber) : Node(lineNumber), needsConversion(false)
{
}

void ExpressionNode::markForConversion(TypeKind target)
{
	targetType = target;
}

void ExpressionNode::setCurrentType(TypeKind actual)
{
	expressionType = actual;
}

