#pragma once
#include "Node.h"
#include "StatementNode.h"
#include "../../analyzer/Symbol.h"

class BlockNode : public Node
{
public:
	BlockNode(int lineNumber);

	// Setters
	void addStatement(std::shared_ptr<StatementNode> statement);
	void addDeclaration(std::shared_ptr<Symbol> symbol);

	// Getters
	std::vector<std::shared_ptr<StatementNode>> getStatements() const;
	std::vector<std::shared_ptr<Symbol>> getDeclarations() const;

private:
	std::vector<std::shared_ptr<StatementNode>> statements;
	std::vector<std::shared_ptr<Symbol>> declarations;

};
