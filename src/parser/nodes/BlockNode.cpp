#include "BlockNode.h"

void BlockNode::addStatement(std::unique_ptr<Statement> statement)
{
	statements.insert(std::move(statement));
}
