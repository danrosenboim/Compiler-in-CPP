#pragma once
#include "ExpressionNode.h"

class FunctionCallExpr : public ExpressionNode
{
public:
    FunctionCallExpr(int lineNumber);

    // Setters
    void setName(const std::string& name);

    // Getters
    std::string getName() const;
    std::vector<std::shared_ptr<ExpressionNode>> getArguments() const;

    // Function to add an argument to the arguments vector
    void addArgument(std::shared_ptr<ExpressionNode> arg);

    // Expression variant
    virtual ExpressionType getExpressionVariant() const override;
private:

    std::string functionName;
    std::vector<std::shared_ptr<ExpressionNode>> arguments;

};