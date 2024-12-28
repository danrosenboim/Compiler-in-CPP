#pragma once
#include <string>
#include <vector>
#include <memory>

// This class will be used as a node for the AST
class Node
{
public:
	Node(Token value);
	~Node() = default;

	/*
	This function adds a new child to the children vector
	Inputs: the new node to add
	Outputs: none
	*/
	void addChild(const Node& node);

	/*
	Function to return the token on request
	Inputs: none
	Outputs: token
	*/
	Token getToken() const;

private:
	const Token token;
	
	std::vector<std::shared_ptr<Node>> children;

};
