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

void FunctionNode::setParameters(std::vector<std::shared_ptr<ParameterNode>>& parameters)
{
	this->parameters.swap(parameters);
}

void FunctionNode::setBody(std::shared_ptr<BlockNode> body)
{
	this->body = std::move(body);
}

TypeKind FunctionNode::getReturnType() const
{
	return returnType;
}

std::string FunctionNode::getName() const
{
	return name;
}

std::vector<std::shared_ptr<ParameterNode>> FunctionNode::getParameters() const
{
	return parameters;
}

std::shared_ptr<BlockNode> FunctionNode::getBody() const
{
	return body;
}

