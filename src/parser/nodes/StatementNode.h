#pragma once
#include "Node.h"

class StatementNode : public Node
{
public:
	StatementNode(int lineNumber);
	virtual ~StatementNode() = default;
};
