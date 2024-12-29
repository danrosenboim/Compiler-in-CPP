#include "StringExpr.h"

StringExpr::StringExpr(int lineNumber, const std::string& value) : ExpressionNode(lineNumber), value(value) {}
