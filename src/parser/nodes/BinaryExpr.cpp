#include "BinaryExpr.h"

BinaryExpr::BinaryExpr(ExpressionType type, std::unique_ptr<ExpressionNode> left, std::unique_ptr<ExpressionNode> right) : type(type), left(std::move(left)), right(std::move(right))
{

}
