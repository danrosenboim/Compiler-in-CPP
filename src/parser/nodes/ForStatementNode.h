#pragma once
#include "Node.h"
#include "StatementNode.h"
#include "ExpressionNode.h"
#include "AssignmentStatementNode.h"
#include "BlockNode.h"

class ForStatementNode : public StatementNode
{
public:
	ForStatementNode(int lineNumber);

	// Setters
	void setVariableName(std::string variableName);
	void setInitExpr(std::shared_ptr<ExpressionNode> initExpr);
	void setCondition(std::shared_ptr<ExpressionNode> condition);
	void setBody(std::shared_ptr<BlockNode> body);
	
	// Getters
	std::string getVariableName() const;
	std::shared_ptr<ExpressionNode> getInitExpr() const;
	std::shared_ptr<ExpressionNode> getCondition() const;
	std::shared_ptr<BlockNode> getBody() const;

	// StatementType
	virtual StatementType getStatementType() const override;

private:
	std::string variableName;
	std::shared_ptr<ExpressionNode> initExpr;
	std::shared_ptr<ExpressionNode> condition;
	std::shared_ptr<BlockNode> body;
};
