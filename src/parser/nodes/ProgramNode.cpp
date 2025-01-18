#include "ProgramNode.h"

ProgramNode::ProgramNode(int lineNumber) : Node(lineNumber)
{ }

void ProgramNode::addFunction(std::shared_ptr<FunctionNode> function)
{
	functions.push_back(function);
}

void ProgramNode::addStatement(std::shared_ptr<StatementNode> statement)
{
	statements.push_back(statement);
}

void ProgramNode::addDeclaration(std::shared_ptr<Symbol> declaration)
{
	globalDeclarations.push_back(declaration);
}

std::vector<std::shared_ptr<FunctionNode>> ProgramNode::getFunctions() const
{
	return functions;
}

std::vector<std::shared_ptr<StatementNode>> ProgramNode::getStatements() const
{
	return statements;
}

std::vector<std::shared_ptr<Symbol>> ProgramNode::getDeclarations() const
{
	return globalDeclarations;
}
