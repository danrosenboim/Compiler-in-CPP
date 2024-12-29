#include "FunctionNode.h"

FunctionNode::FunctionNode(int lineNumber) : Node(lineNumber)
{}

void FunctionNode::setReturnType(TypeKind returnType)
{
	this->returnType = returnType;
}

void FunctionNode::setName(std::string functionName)
{
	name = functionName;
}

void FunctionNode::setParameters(std::vector<std::unique_ptr<ParameterNode>> parameters)
{
	for (auto& i : parameters)
	{
		parameters.push_back(std::move(i));
	}
}

void FunctionNode::setBody(std::unique_ptr<BlockNode> body)
{
	this->body = std::move(body);
}

