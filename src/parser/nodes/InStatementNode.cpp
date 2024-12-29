#include "OutStatementNode.h"
#include "InStatementNode.h"


InStatementNode::InStatementNode(int lineNumber) : StatementNode(lineNumber)
{
}

void InStatementNode::setIdentifier(std::string id)
{
	this->identifier = id;
}
