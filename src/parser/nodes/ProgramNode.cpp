#include "ProgramNode.h"

ProgramNode::ProgramNode(int lineNumber) : Node(lineNumber)
{ }

void ProgramNode::addFunction(std::unique_ptr<FunctionNode> function)
{
	functions.push_back(std::move(function));
}

void ProgramNode::addStatement(std::unique_ptr<StatementNode> statement)
{
	statements.push_back(std::move(statement));
}
