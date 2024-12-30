#include "FunctionCallExpr.h"

FunctionCallExpr::FunctionCallExpr(int lineNumber) : ExpressionNode(lineNumber)
{
}

void FunctionCallExpr::setName(const std::string& name)
{
	this->functionName = name;
}

void FunctionCallExpr::addArgument(std::shared_ptr<ExpressionNode> arg)
{
	arguments.push_back(std::move(arg));
}
