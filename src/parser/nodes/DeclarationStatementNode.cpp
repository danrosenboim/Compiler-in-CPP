#include "DeclarationStatementNode.h"

DeclarationStatementNode::DeclarationStatementNode(int lineNumber) : StatementNode(lineNumber)
{
}

void DeclarationStatementNode::setType(TypeKind type)
{
	this->type = type;
}

void DeclarationStatementNode::setIdentifier(std::string id)
{
	this->identifier = id;
}

void DeclarationStatementNode::setInitializer(std::shared_ptr<ExpressionNode> expression)
{
	this->initializer = std::move(expression);
}
