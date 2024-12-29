#pragma once
#include "Node.h"
#include "../lexer/Lexer.h"


// Parser class will use the previously built lexer to create an AST
class Parser
{
public:
	Parser::Parser(std::shared_ptr<Lexer> scanner);
	
	/*
	Parses the whole program
	Inputs: none
	Outputs: head of the AST tree
	*/
	std::shared_ptr<Node> parseProgram();

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
	Function type that checks if the token type is a comparison operator(== >=...)
	Inputs: type - the type you want to check
	Outputs: returns true if it is a comparison operator otherwise false.
	*/
	bool isComparisonOp(TokenType type);


	// Different variations of creating a node
	// Return value is a shared pointer to the created node
	static std::shared_ptr<Node> createNode(NodeType type, Token token);
	static std::shared_ptr<Node> createNode(NodeType type, TokenType tokenType, int lineNumber);
	static std::shared_ptr<Node> createNode(NodeType type, TokenType tokenType);
	static std::shared_ptr<Node> createNode(NodeType type);

	
	// Parse functions that return a node
	std::shared_ptr<Node> parseFunction();
	std::shared_ptr<Node> parseType();
	std::shared_ptr<Node> parseIdentifier();
	std::shared_ptr<Node> parseParameters();
	std::shared_ptr<Node> parseParameter();
	std::shared_ptr<Node> parseBlock();
	std::shared_ptr<Node> parseStatement();
	
	// Parse statement functions
	std::shared_ptr<Node> parseForStatement();
	std::shared_ptr<Node> parseIfStatement();
	std::shared_ptr<Node> parseElsePart();
	std::shared_ptr<Node> parseReturnStatement();
	std::shared_ptr<Node> parseOutStatement();
	std::shared_ptr<Node> parseInStatement();
	std::shared_ptr<Node> parseAssignmentStatement();

	// Parse expression functions
	std::shared_ptr<Node> parseExpression();
	std::shared_ptr<Node> parseTerm1();
	std::shared_ptr<Node> parseTerm2();
	std::shared_ptr<Node> parseFactor();
};
