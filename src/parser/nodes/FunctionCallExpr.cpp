#include "FunctionCallExpr.h"

FunctionCallExpr::FunctionCallExpr(int lineNumber) : ExpressionNode(lineNumber)
{
}

void FunctionCallExpr::setName(const std::string& name)
{
	this->functionName = name;
}

std::string FunctionCallExpr::getName() const
{
	return functionName;
}

std::vector<std::shared_ptr<ExpressionNode>> FunctionCallExpr::getArguments() const
{
	return arguments;
}

void FunctionCallExpr::addArgument(std::shared_ptr<ExpressionNode> arg)
{
	arguments.push_back(std::move(arg));
}

ExpressionType FunctionCallExpr::getExpressionVariant() const
{
	return ExpressionType::FUNC_CALL;
}
