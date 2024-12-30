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
	void addStatement(std::shared_ptr<StatementNode> statement);

	std::vector<std::shared_ptr<StatementNode>> getStatements() const;

private:
	std::vector<std::shared_ptr<StatementNode>> statements;

};
