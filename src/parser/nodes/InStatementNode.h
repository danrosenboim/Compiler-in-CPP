#pragma once
#include "StatementNode.h"
#include "ExpressionNode.h"
#include "IdentifierExpr.h"

class InStatementNode : public StatementNode
{
public:
	InStatementNode(int lineNumber);

	void setIdentifier(std::string id);
private:
	std::string identifier;
};