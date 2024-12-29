#pragma once
#include "StatementNode.h"
#include "ExpressionNode.h"
#include "IdentifierExpr.h"

class InStatementNode : public StatementNode
{
public:
	InStatementNode(std::string identifier);

private:
	std::string identifier;
}
