#pragma once
#include <string>
#include <vector>
#include <memory>
#include "NodeType.h"

// This class will be used as a node for the AST
class Node
{
public:
	Node(NodeType type, Token token);
	~Node() = default;

	/*
	This function adds a new child to the children vector
	Inputs: the new node to add
	Outputs: none
	*/
	void addChild(std::shared_ptr<Node> node);

	/*
	Function to return the token on request
	Inputs: none
	Outputs: token
	*/
	Token getToken() const;

private:
	// Type and token for value tracking and type
	const NodeType type;
	const Token token;

	// Keep track of all the nodes' children
	std::vector<std::shared_ptr<Node>> children;

};
