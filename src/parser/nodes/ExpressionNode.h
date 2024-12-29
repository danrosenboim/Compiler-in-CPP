#pragma once
#include "Node.h"

class ExpressionNode : public Node
{
public:
	ExpressionNode(int lineNumber);
	virtual ~ExpressionNode() = default;
};
