#pragma once
#include "Node.h"
#include "TypeKind.h"

class ParameterNode : public Node
{
public:
	ParameterNode(int lineNumber);

	// Setters for each variable
	void setType(TypeKind type);
	void setIdentifier(std::string identifier);

private:
	TypeKind type;
	std::string identifier;
};
