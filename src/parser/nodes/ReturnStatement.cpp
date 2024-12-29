#include "ReturnStatement.h"

ReturnStatement::ReturnStatement(std::unique_ptr<ExpressionNode> expression) : expression(std::move(expression))
{

}
