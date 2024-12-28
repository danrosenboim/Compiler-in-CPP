#include "Node.h"

Node::Node(Token token) : token(token)
{
	
}

void Node::addChild(const Node& node)
{
	// Insert a new shared pointer into the children list
	children.insert(std::make_shared<Node>(node));
}

Token Node::getToken() const
{
	return token;
}
