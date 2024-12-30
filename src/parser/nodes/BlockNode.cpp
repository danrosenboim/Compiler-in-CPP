#include "BlockNode.h"

BlockNode::BlockNode(int lineNumber) : Node(lineNumber)
{
}

void BlockNode::addStatement(std::shared_ptr<StatementNode> statement)
{
	statements.push_back(std::move(statement));
}
