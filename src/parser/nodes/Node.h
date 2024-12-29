#pragma once
#include <string>
#include <vector>
#include <memory>

// Forward declarations
class ExpressionNode;
class StatementNode;
class ParameterNode;

// This class will be used as a node for the AST
class Node
{
public:
	Node(int lineNumber);
	virtual ~Node() = default;

	/*
	Returns the line number
	Inputs: none
	Outputs: line number of the node
	*/
	int getLineNumber() const;


private:
	
	// Keep track of the line number
	int m_lineNumber;

};
