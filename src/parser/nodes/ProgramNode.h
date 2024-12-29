#pragma once
#include "Node.h"
#include <vector>
#include "FunctionNode.h"
#include "StatementNode.h"

class ProgramNode : public Node
{
public:

	void addFunction(std::unique_ptr<FunctionNode> function);
	void addStatement(std::unique_ptr<StatementNode> statement);

private:
	std::vector<std::unique_ptr<FunctionNode>> functions;
	std::vector<std::unique_ptr<StatementNode>> statements;
}
