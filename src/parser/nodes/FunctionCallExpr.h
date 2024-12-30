#pragma once
#include "ExpressionNode.h"

class FunctionCallExpr : public ExpressionNode
{
public:
    FunctionCallExpr(int lineNumber);

    void setName(const std::string& name);

    void addArgument(std::shared_ptr<ExpressionNode> arg);
private:

    std::string functionName;
    std::vector<std::shared_ptr<ExpressionNode>> arguments;

};