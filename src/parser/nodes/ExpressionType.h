#pragma once

enum class ExpressionType
{
	BINARY, NUMBER, REAL, BOOL,
	STRING, IDENTIFIER, FUNC_CALL,
	NOT, ERROR
};