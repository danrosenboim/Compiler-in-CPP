#include "StatementNode.h"

StatementNode::StatementNode(int lineNumber) : Node(lineNumber)
{
}

StatementType StatementNode::getStatementType() const
{
    return StatementType::ERROR;
}
