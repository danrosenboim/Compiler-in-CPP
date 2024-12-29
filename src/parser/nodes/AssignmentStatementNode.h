#pragma once
#include "Node.h"
#include "StatementNode.h"

class AssignmentStatement : public StatementNode
{
public:
	AssignmentStatement(std::string identifier, std::unique_ptr<ExpressionNode> expression);

private:
	std::string identifier;
	std::unique_ptr<ExpressionNode> expression;
}
