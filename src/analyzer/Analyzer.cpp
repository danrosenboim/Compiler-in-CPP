#include "Analyzer.h"

Analyzer::Analyzer()
{
}

bool Analyzer::canConvert(TypeKind from, TypeKind to)
{
	// Check for the same type
	if(from == to)
	{
		return true;
	}
	if(to != TypeKind::TEXT)
	{
		return true;
	}
	return false;
}



