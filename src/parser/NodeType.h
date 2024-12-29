#pragma once

enum NodeType
{
	// Main
	PROGRAM, EXPRESSION, BLOCK,

	// Expression
	FACTOR, TERM2, TERM1,
	
	// Statements
	FOR, IF, RETURN, OUT, IN, ASSIGNMENT,

	// Function
	FUNCTION, TYPE, PARAMETERS, PARAMETER, IDENTIFIER

};
