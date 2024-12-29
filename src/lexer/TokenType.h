#pragma once

enum class TokenType
{
	// Single-character tokens
	LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
	COMMA, SEMICOLON,

	// Operators
	MINUS, PLUS, SLASH, STAR,
	EQUAL, EQUAL_EQUAL,
	GREATER, GREATER_EQUAL,
	LESS, LESS_EQUAL,
	NOT, NOT_EQUAL,

	// Literals
	IDENTIFIER, TEXT, NUMBER, REAL, BOOLEAN,

	// Types
	STRING, INT, FLOAT, BOOL,

	// Keywords
	IF, THEN, ELSE, WHILE, TRUE, FALSE,
	FOR, UNTIL, FUNCTION, RETURN, OUT, IN,

	// Skippable
	WHITESPACE, COMMENT,

	END_OF_FILE,
	
};

