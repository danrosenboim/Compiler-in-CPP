#include "ParameterNode.h"

ParameterNode::ParameterNode(std::unique_ptr<TypeNode> type, std::string id) : type(std::move(type)), identifier(id)
{
}
