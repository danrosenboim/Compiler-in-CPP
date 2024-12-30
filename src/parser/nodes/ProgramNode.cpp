#include "ProgramNode.h"

ProgramNode::ProgramNode(int lineNumber) : Node(lineNumber)
{ }

void ProgramNode::addFunction(std::shared_ptr<FunctionNode> function)
{
	functions.push_back(std::move(function));
}

void ProgramNode::addStatement(std::shared_ptr<StatementNode> statement)
{
	statements.push_back(std::move(statement));
}

std::vector<std::shared_ptr<FunctionNode>> ProgramNode::getFunctions() const
{
	return functions;
}

std::vector<std::shared_ptr<StatementNode>> ProgramNode::getStatements() const
{
	return statements;
}
