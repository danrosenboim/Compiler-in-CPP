#include "OutStatementNode.h"

OutStatementNode::OutStatementNode(std::unique_ptr<ExpressionNode> expression) : expression(std::move(expression))
{}
