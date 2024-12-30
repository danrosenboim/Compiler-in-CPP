#pragma once
#pragma once
#include "Node.h"
#include "ExpressionNode.h"
#include "StatementNode.h"

class DeclarationStatementNode : public StatementNode
{
public:
	DeclarationStatementNode(int lineNumber);

	// Setters
	void setType(TypeKind type);
	void setIdentifier(std::string id);
	void setInitializer(std::shared_ptr<ExpressionNode> expression);

	// Getters
	TypeKind getType() const;
	std::string getIdentifier() const;
	std::shared_ptr<ExpressionNode> getInitializer() const;

	// StatementType
	virtual StatementType getStatementType() const override;

private:
	TypeKind type;
	std::string identifier;
	std::shared_ptr<ExpressionNode> initializer;
};
