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
	Function that creates a node with a speicified line number
	Inputs: type of the node, type of the token
	Outputs: returns a shared pointer to the created node
	*/
	static std::shared_ptr<Node> createNode(NodeType type, TokenType tokenType, int lineNumber);
	/*
	Function that creates a node
	Inputs: type of the node, type of the token
	Outputs: returns a shared pointer to the created node
	*/
	static std::shared_ptr<Node> createNode(NodeType type, TokenType tokenType);
	
	/*
	Function that creates a node without a token
	Inputs: type of the node
	Outputs: shared pointer to the created node
	*/
	static std::shared_ptr<Node> createNode(NodeType type);

	
	// Parse functions that return a node
	std::shared_ptr<Node> parseFunction();
	std::shared_ptr<Node> parseType();
};
