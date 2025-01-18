#pragma once
#include "TokenType.h"
#include <iostream>
#include <variant>

// This class will be used as a token for the lexer
class Token
{
public:
	// Different constructors to initialize the union
	Token(TokenType tag, int lineNumber);
	Token(TokenType tag, std::string s, int lineNumber);
	Token(TokenType tag, int i, int lineNumber);
	Token(TokenType tag, float f, int lineNumber);
	Token(TokenType tag, bool b, int lineNumber);

	// Copy constructor
	Token(const Token& other);

	// Get functions for all the variables
	TokenType getTag() const;
	int getLineNumber() const;

	std::string getLexeme() const;
	int getNumber() const;
	float getReal() const;
	bool getBool() const;
	
	// Function to help printing, converts from TokenType to a readable string
	static std::string typeToString(TokenType type);

	// Copy for token
	Token& operator=(const Token& other);

	// Helping with print
	friend std::ostream& operator<<(std::ostream& os, const Token& token);


private:
	// What type of token we are deeling with.
	TokenType m_tag;

	// Line number for error report, as needed
	int m_lineNumber;

	// (not using union because it doesnt support std::string and less reliable)
	// Variant allows us to create different types of variables using the same memory location	
	std::variant<std::string, int, float, bool> m_value;

};
