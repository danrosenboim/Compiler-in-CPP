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
	void setParameters(std::vector<std::shared_ptr<ParameterNode>>& parameters);
	void setBody(std::shared_ptr<BlockNode> body);

	// Getters
	TypeKind getReturnType() const;
	std::string getName() const;
	std::vector<std::shared_ptr<ParameterNode>> getParameters() const;
	std::shared_ptr<BlockNode> getBody() const;


private:
	TypeKind returnType;
	std::string name;
	std::vector<std::shared_ptr<ParameterNode>> parameters;
	std::shared_ptr<BlockNode> body;
};
