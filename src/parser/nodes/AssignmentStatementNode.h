#pragma once
#include "Node.h"
#include "ExpressionNode.h"
#include "StatementNode.h"

class AssignmentStatementNode : public StatementNode
{
public:
	AssignmentStatementNode(int lineNumber);

	void setIdentifier(std::string id);
	void setExpression(std::shared_ptr<ExpressionNode> expression);

private:
	std::string identifier;
	std::shared_ptr<ExpressionNode> expression;
};
