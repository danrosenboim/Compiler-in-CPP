#pragma once
#include "Node.h"

class ParameterNode : public Node
{
public:
	ParameterNode(std::unique_ptr<TypeNode> type, std::string id);

private:
	std::unique_ptr<TypeNode> type;
	std::string identifier;
}
