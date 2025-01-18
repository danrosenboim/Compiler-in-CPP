#pragma once

enum class BinaryExprType
{
	// Basic operations
	ADD, SUB, MUL, DIV,

	// Comparison
	GREATER, GREATER_EQUAL,
	EQUAL_EQUAL,
	LESS, LESS_EQUAL,
	NOT_EQUAL
};
