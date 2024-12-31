#pragma once
#include "ExpressionNode.h"

class NotExpr : public ExpressionNode
{
public:
    NotExpr(int lineNumber);

    void setExpression(std::shared_ptr<ExpressionNode> expression);

    // Getters
    std::shared_ptr<ExpressionNode> getExpression() const;

    // Expression variant
    virtual ExpressionType getExpressionVariant() const override;

private:
    std::shared_ptr<ExpressionNode> expression;
};

