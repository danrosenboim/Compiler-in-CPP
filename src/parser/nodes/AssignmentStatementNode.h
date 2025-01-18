#pragma once
#include "Node.h"
#include "ExpressionNode.h"
#include "StatementNode.h"

class AssignmentStatementNode : public StatementNode
{
public:
	AssignmentStatementNode(int lineNumber);

	// Function setters
	void setIdentifier(std::string id);
	void setExpression(std::shared_ptr<ExpressionNode> expression);

	// Getters
	std::string getIdentifier() const;
	std::shared_ptr<ExpressionNode> getExpression() const;

	// StatementType
	virtual StatementType getStatementType() const override;

private:
	std::string identifier;
	std::shared_ptr<ExpressionNode> expression;
};
