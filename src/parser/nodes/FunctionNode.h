#pragma once
#include "Node.h"
#include "TypeKind.h"
#include "BlockNode.h"
#include "ParameterNode.h"

class FunctionNode : public Node
{
public:
	FunctionNode(int lineNumber);

	// Set functions for all the variables
	void setReturnType(TypeKind returnType);
	void setName(const std::string& functionName);
	void setParameters(std::vector<std::unique_ptr<ParameterNode>>& parameters);
	void setBody(std::unique_ptr<BlockNode> body);


private:
	TypeKind returnType;
	std::string name;
	std::vector<std::unique_ptr<ParameterNode>> parameters;
	std::unique_ptr<BlockNode> body;
};
