#include "BlockNode.h"

BlockNode::BlockNode(int lineNumber) : Node(lineNumber)
{
}

void BlockNode::addStatement(std::shared_ptr<StatementNode> statement)
{
	statements.push_back(std::move(statement));
}

void BlockNode::addDeclaration(std::shared_ptr<Symbol> symbol)
{
	declarations.push_back(symbol);
}

std::vector<std::shared_ptr<StatementNode>> BlockNode::getStatements() const
{
	return statements;
}

std::vector<std::shared_ptr<Symbol>> BlockNode::getDeclarations() const
{
	return declarations;
}
