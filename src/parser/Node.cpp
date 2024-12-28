#include "Node.h"

Node::Node(NodeType type, std::unique_ptr<Token> token) : type(type) token(std::move(token))
{
	
}

void Node::addChild(std::shared_ptr<Node> node)
{
	// Insert a new shared pointer into the children list
	children.insert(node);
}

Token Node::getToken() const
{
	// Create a copy of the token
	return Token(*token);
}
