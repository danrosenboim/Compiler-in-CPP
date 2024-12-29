#pragma once
#include "ExpressionNode.h"

class NotExpr : public ExpressionNode
{
public:
    NotExpr(int lineNumber);

    void setExpression(std::unique_ptr<ExpressionNode> expression);

private:
    std::unique_ptr<ExpressionNode> expression;
};

