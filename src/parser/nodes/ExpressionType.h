#pragma once

enum class ExpressionType
{
	// Basic operations
	ADD, SUB, MUL, DIV,

	// Comparison
	GREATER, GREATER_EQUAL,
	EQUAL_EQUAL,
	LESS, LESS_EQUAL,
	NOT, NOT_EQUAL,

	FUNCTION_CALL
};
