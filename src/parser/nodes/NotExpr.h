#pragma once
#include "ExpressionNode.h"

class NotExpr : public ExpressionNode
{
public:
    NotExpr(int lineNumber);

    void setExpression(std::shared_ptr<ExpressionNode> expression);

private:
    std::shared_ptr<ExpressionNode> expression;
};

