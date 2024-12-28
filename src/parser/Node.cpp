#include "Node.h"

Node::Node(NodeType type, Token token) : type(type) token(token)
{
	
}

void Node::addChild(std::shared_ptr<Node> node)
{
	// Insert a new shared pointer into the children list
	children.insert(node);
}

Token Node::getToken() const
{
	return token;
}
