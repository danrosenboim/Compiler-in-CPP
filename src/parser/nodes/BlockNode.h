#pragma once
#include "Node.h"
#include "StatementNode.h"

class BlockNode : public Node
{
public:
	BlockNode(int lineNumber);

	// Function to add a statement
	// Inputs: new statement
	// Outputs: none
	void addStatement(std::unique_ptr<StatementNode> statement);

private:
	std::vector<std::unique_ptr<StatementNode>> statements;

};
