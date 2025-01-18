#pragma once
#include "Node.h"
#include <vector>
#include "FunctionNode.h"
#include "StatementNode.h"
#include "DeclarationStatementNode.h"
#include "../../analyzer/Symbol.h"

class ProgramNode : public Node
{
public:
	ProgramNode(int lineNumber);

	// Getters
	std::vector<std::shared_ptr<FunctionNode>> getFunctions() const;
	std::vector<std::shared_ptr<StatementNode>> getStatements() const;
	std::vector<std::shared_ptr<Symbol>> getDeclarations() const;
	
	// Add items to the current vectors
	void addFunction(std::shared_ptr<FunctionNode> function);
	void addStatement(std::shared_ptr<StatementNode> statement);
	void addDeclaration(std::shared_ptr<Symbol> declaration);

private:
	// Functions in the code will be added here
	std::vector<std::shared_ptr<FunctionNode>> functions;

	// Statements will be added here
	std::vector<std::shared_ptr<StatementNode>> statements;

	// Will be added in semantic analysis phase and used in code generation
	std::vector<std::shared_ptr<Symbol>> globalDeclarations;
};
