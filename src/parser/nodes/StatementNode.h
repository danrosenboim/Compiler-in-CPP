#pragma once
#include "Node.h"
#include "StatementType.h"

class StatementNode : public Node
{
public:
	StatementNode(int lineNumber);
	virtual ~StatementNode() = default;

	// This will help us determine what type of statement the statement is even though
	// were using inheritence
	// Usually I would make this a pure function but
	// Making it return an error flag would be more beneficial
	// as it would help us give more info to the user
	virtual StatementType getStatementType() const;
};
