#include "AssignmentStatementNode.h"

AssignmentStatement(std::string identifier, std::unique_ptr<ExpressionNode> expression) : identifier(identifier), expression(std::move(expression)) {}

