#pragma once
#include "Node.h"
#include "StatementNode.h"
#include "ExpressionNode.h"
#include "BlockNode.h"

class ForStatementNode : public StatementNode
{
public:
	ForStatementNode(int lineNumber);

	void setVariableName(std::string variableName);
	void setInitExpr(std::unique_ptr<ExpressionNode> initExpr);
	void setCondition(std::unique_ptr<ExpressionNode> condition);
	void setBody(std::unique_ptr<BlockNode> body);
	
private:
	std::string variableName;
	std::unique_ptr<ExpressionNode> initExpr;
	std::unique_ptr<ExpressionNode> condition;
	std::unique_ptr<BlockNode> body;
};
