#pragma once
#pragma once
#include "Node.h"
#include "ExpressionNode.h"
#include "StatementNode.h"

class DeclarationStatementNode : public StatementNode
{
public:
	DeclarationStatementNode(int lineNumber);

	void setType(TypeKind type);
	void setIdentifier(std::string id);
	void setInitializer(std::shared_ptr<ExpressionNode> expression);

private:
	TypeKind type;
	std::string identifier;
	std::shared_ptr<ExpressionNode> initializer;
};
