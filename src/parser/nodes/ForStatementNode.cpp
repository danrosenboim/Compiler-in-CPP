#include "ForStatementNode.h"

ForStatementNode::ForStatementNode(std::string variable, std::unique_ptr<ExpressionNode> initExpr, std::unique_ptr<ExpressionNode> condition, std::unique_ptr<BlockNode> body) : variable(variable), initExpr(std::move(initExpr)), condition(std::move(condition)), body(std::move(body))
{
}
