#include "FunctionNode.h"

FunctionNode::FunctionNode(int lineNumber) : Node(lineNumber)
{}

void FunctionNode::setReturnType(TypeKind returnType)
{
	this->returnType = returnType;
}

void FunctionNode::setName(const std::string& functionName)
{
	name = functionName;
}

void FunctionNode::setParameters(std::vector<std::unique_ptr<ParameterNode>>& parameters)
{
	this->parameters.swap(parameters);
}

void FunctionNode::setBody(std::unique_ptr<BlockNode> body)
{
	this->body = std::move(body);
}

