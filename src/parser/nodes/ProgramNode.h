#pragma once
#include "Node.h"
#include <vector>
#include "FunctionNode.h"
#include "StatementNode.h"

class ProgramNode : public Node
{
public:
	ProgramNode(int lineNumber);

	void addFunction(std::shared_ptr<FunctionNode> function);
	void addStatement(std::shared_ptr<StatementNode> statement);

	std::vector<std::shared_ptr<FunctionNode>> getFunctions() const;
	std::vector<std::shared_ptr<StatementNode>> getStatements() const;

private:
	std::vector<std::shared_ptr<FunctionNode>> functions;
	std::vector<std::shared_ptr<StatementNode>> statements;
};
