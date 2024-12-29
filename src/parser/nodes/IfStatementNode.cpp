#include "IfStatementNode.h"

IfStatementNode::IfStatement(std::unique_ptr<ExpressionNode> condition, std::unique_ptr<BlockNode> body, std::unique_ptr<BlockNode> elseBlock) : condition(std::move(condition)), body(std::move(body)), elseBlock(std::move(elseBlock))
{
}

