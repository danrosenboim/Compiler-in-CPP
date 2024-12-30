#pragma once
#include "StatementNode.h"
#include "ExpressionNode.h"
#include "IdentifierExpr.h"

class InStatementNode : public StatementNode
{
public:
	InStatementNode(int lineNumber);

	// Setter
	void setIdentifier(std::string id);
	
	// Getter
	std::string getIdentifier() const;

	// StatementType
	virtual StatementType getStatementType() const override;

private:
	std::string identifier;
};