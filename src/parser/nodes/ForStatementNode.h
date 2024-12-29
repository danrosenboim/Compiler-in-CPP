#pragma once
#include "StatementNode.h"
#include "ExpressionNode.h"
#include "BlockNode.h"

class ForStatementNode : public StatementNode
{
public:
	ForStatementNode(std::string variable, std::unique_ptr<ExpressionNode> initExpr, std::unique_ptr<ExpressionNode> condition, std::unique_ptr<BlockNode> body);
	
private:
	std::string variable;
	std::unique_ptr<ExpressionNode> initExpr;
	std::unique_ptr<ExpressionNode> condition;
	std::unique_ptr<Block> body;
};
