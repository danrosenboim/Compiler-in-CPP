#include "ExpressionNode.h"

ExpressionNode::ExpressionNode(int lineNumber) : Node(lineNumber), needsConversion(false)
{
}

void ExpressionNode::markForConversion(TypeKind target)
{
	needsConversion = true;
	targetType = target;
}

void ExpressionNode::setCurrentType(TypeKind actual)
{
	expressionType = actual;
}

TypeKind ExpressionNode::getExpressionType() const
{
	return expressionType;
}

TypeKind ExpressionNode::getTargetType() const
{
	return targetType;
}

bool ExpressionNode::getNeedsConversion() const
{
	return needsConversion;
}

ExpressionType ExpressionNode::getExpressionVariant() const
{
	return ExpressionType::ERROR;
}

