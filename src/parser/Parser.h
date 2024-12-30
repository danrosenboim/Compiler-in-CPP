#pragma once
#include "../lexer/Lexer.h"
#include "../exceptions/parser/ParserUnexpected.h"
#include "nodes/AssignmentStatementNode.h"
#include "nodes/DeclarationStatementNode.h"
#include "nodes/BinaryExpr.h"
#include "nodes/BlockNode.h"
#include "nodes/ExpressionNode.h"
#include "nodes/ExpressionType.h"
#include "nodes/ForStatementNode.h"
#include "nodes/IfStatementNode.h"
#include "nodes/FunctionNode.h"
#include "nodes/IdentifierExpr.h"
#include "nodes/InStatementNode.h"
#include "nodes/Node.h"
#include "nodes/NumberExpr.h"
#include "nodes/OutStatementNode.h"
#include "nodes/ParameterNode.h"
#include "nodes/ProgramNode.h"
#include "nodes/RealExpr.h"
#include "nodes/BoolExpr.h"
#include "nodes/ReturnStatementNode.h"
#include "nodes/StatementNode.h"
#include "nodes/StringExpr.h"
#include "nodes/NotExpr.h"
#include "nodes/FunctionCallExpr.h"
#include "nodes/TypeKind.h"


// Parser class will use the previously built lexer to create an AST
class Parser
{
public:
	Parser(std::shared_ptr<Lexer> scanner);
	
	/*
	Parses the whole program
	Inputs: none
	Outputs: head of the AST tree
	*/
	std::unique_ptr<ProgramNode> parseProgram();

private:
	// Scanner that will return tokens on demand
	std::shared_ptr<Lexer> scanner;

	// Current token that were on
	Token currentToken;

	/*
	Function to advance and generate a new token
	Inputs: none
	Outputs: none
	*/
	void advance();


	/*
	Function that checks if the type the program expects equals the one that it got
	Inputs: token that it expects
	Outputs: true if it advanced false if not.
	*/
	bool match(TokenType type);
	
	/*
	Function similar to match, however if it returns false an error occurres
	Inputs: expectation
	Outputs: none
	*/
	void expect(TokenType type);

	/*
	Function type that checks if the token type is a comparison operator(== >=...) then returns that operator.
	Inputs: type - the type you want to check, a reference to an expression type so it can change it
	Outputs: returns true if it is a comparison operator otherwise false.
	*/
	bool isComparisonOp(TokenType type, ExpressionType& exType);

	/*
	Uses the current token to determine what type it should return
	Inputs: none
	Outputs: the type
	*/
	TypeKind parseType();

	/*
	Uses the current token to get an identifier
	Inputs: none
	Outputs: name of the identifier
	*/
	std::string parseIdentifier();

	// Parse functions that return a node
	std::shared_ptr<FunctionNode> parseFunction();
	std::vector<std::shared_ptr<ParameterNode>> parseParameters();
	std::shared_ptr<ParameterNode> parseParameter();
	std::shared_ptr<BlockNode> parseBlock();
	std::shared_ptr<StatementNode> parseStatement();
	
	// Parse statement functions
	std::shared_ptr<ForStatementNode> parseForStatement();
	std::shared_ptr<IfStatementNode> parseIfStatement();
	std::shared_ptr<ReturnStatementNode> parseReturnStatement();
	std::shared_ptr<OutStatementNode> parseOutStatement();
	std::shared_ptr<InStatementNode> parseInStatement();
	std::shared_ptr<DeclarationStatementNode> parseDeclarationStatement();
	std::shared_ptr<AssignmentStatementNode> parseAssignmentStatement();

	// Parse expression functions
	std::shared_ptr<ExpressionNode> parseExpression();
	std::shared_ptr<ExpressionNode> parseTerm1();
	std::shared_ptr<ExpressionNode> parseTerm2();
	std::shared_ptr<ExpressionNode> parseFactor();
};
