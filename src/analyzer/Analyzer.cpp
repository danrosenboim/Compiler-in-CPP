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
	if(to != TypeKind::TEXT || from != TypeKind::TEXT)
	{
		return true;
	}
	return false;
}

void Analyzer::analyze(std::unique_ptr<ProgramNode> programNode)
{
	// Loop through all the function declarations and add them
	for (const auto& func : programNode->getFunctions())
	{
		registerFunction(func);
	}
}

void Analyzer::registerFunction(std::shared_ptr<FunctionNode> func)
{
	// Check for function redefinition
	if (symbolTable->tableLookup(func->getName()) != nullptr)
	{
		// TODO ADD ERRORS
		//throw SemanticError("Function " + func->getName() + " redefined at line " + std::to_string(func->getLineNumber()));
		throw std::exception();
	}

	// Register function in global scope
	Symbol funcSymbol(SymbolType::GLOBAL, func->getReturnType(), func->getName(), 0);
	symbolTable->addEntryToLatest(funcSymbol);
}


