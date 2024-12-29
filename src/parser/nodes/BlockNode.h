#pragma once
#include "Node.h"

class BlockNode : public Node
{
public:
	BlockNode() = default;

	// Function to add a statement
	// Inputs: new statement
	// Outputs: none
	void addStatement(std::unique_ptr<Statement> statement);

private:
	std::vector<std::unique_ptr<Statement>> statements;

};
