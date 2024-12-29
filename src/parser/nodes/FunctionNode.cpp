#include "FunctionNode.h"

FunctionNode::FunctionNode(TypeKind returnType, std::string name, std::vector<std::unique_ptr<ParameterNode>> parameters,
		std::unique_ptr<BlockNode> body) : returnType(returnType), name(name), parameters(std::move(parameters)), body(std::move(body))
{}
