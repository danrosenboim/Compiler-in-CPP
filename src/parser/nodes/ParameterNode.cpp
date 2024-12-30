#include "ParameterNode.h"


ParameterNode::ParameterNode(int lineNumber) : Node(lineNumber), type(TypeKind::TEXT)
{
}

void ParameterNode::setType(TypeKind type)
{
	this->type = type;
}

void ParameterNode::setIdentifier(std::string identifier)
{
	this->identifier = identifier;
}

TypeKind ParameterNode::getType() const
{
	return type;
}

std::string ParameterNode::getIdentifier() const
{
	return identifier;
}
