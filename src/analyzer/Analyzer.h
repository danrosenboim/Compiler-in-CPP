#pragma once
#include "SymbolTable.h"
#include "../parser/nodes/ProgramNode.h"
#include "../parser/nodes/AssignmentStatementNode.h"
#include "../parser/nodes/BinaryExpr.h"
#include "../parser/nodes/NotExpr.h"
#include "../parser/nodes/IdentifierExpr.h"
#include "../parser/nodes/FunctionCallExpr.h"
#include "../parser/nodes/DeclarationStatementNode.h"
#include "../parser/nodes/ForStatementNode.h"
#include "../parser/nodes/InStatementNode.h"
#include "../parser/nodes/OutStatementNode.h"
#include "../parser/nodes/FunctionNode.h"
#include "../parser/nodes/ReturnStatementNode.h"
#include "../exceptions/analyzer/AnalyzerCannotConvert.h"
#include "../exceptions/analyzer/AnalyzerCannotPerformOnText.h"
#include "../exceptions/analyzer/AnalyzerFunctionRedefined.h"
#include "../exceptions/analyzer/AnalyzerUndefinedVariable.h"
#include "../exceptions/analyzer/AnalyzerVarDefined.h"
#include "../exceptions/analyzer/AnalyzerInvalidArgCount.h"
#include "../exceptions/analyzer/AnalyzerCannotCallVariable.h"
#include "../exceptions/analyzer/AnalyzerCannotReturnInGlobal.h"

class Analyzer
{
public:
	Analyzer();

	/*
	Function that analyzes the file and checks the types
	Inputs: the head output node
	Outputs: none
	*/
	void analyze(std::unique_ptr<ProgramNode> programNode);
	
private:
	// Symbol table to keep track of all the variables and functions
	std::unique_ptr<SymbolTable> symbolTable;

	// Instead of passing this variable around we can keep track of the current function were in using
	// this variable.
	TypeKind currentFunctionReturnType;

	/*
	 * Checks if one type can convert to the other
	 * Inputs: from, to, types to check
	 * Outputs: bool, return true or false if you can convert from one type to the other
	 * */
	static bool canConvert(TypeKind from, TypeKind to);

	/*
	Makes 2 expressions with different types work by converting one
	Inputs: 2 expressions, and their types
	Outputs: the type of both of them combined
	*/
	TypeKind convertBinaryOperation(TypeKind type1, TypeKind type2, std::shared_ptr<ExpressionNode> expr1, std::shared_ptr<ExpressionNode> expr2);

	/*
	Function that converts TypeKind
	Inputs: the type to convert to a string
	Outputs: returns a string
	*/
	static std::string typeKindToString(TypeKind type);

	/*
	This function registers a function
	Inputs: Function node
	Outputs: none
	*/
	void registerFunction(std::shared_ptr<FunctionNode> func);

	/*
	Following analyzer functions to type check everything and make sure there are no symbol redefenitions.
	*/
	void analyzeFunction(std::shared_ptr<FunctionNode> func);
	void analyzeBlock(std::shared_ptr<BlockNode> block);
	void analyzeStatement(std::shared_ptr<StatementNode> statement);
	void analyzeAssignment(std::shared_ptr<AssignmentStatementNode> assignment);
	void analyzeDeclaration(std::shared_ptr<DeclarationStatementNode> declaration);
	void analyzeFor(std::shared_ptr<ForStatementNode> forNode);
	void analyzeIf(std::shared_ptr<IfStatementNode> ifNode);
	void analyzeIn(std::shared_ptr<InStatementNode> inNode);
	void analyzeOut(std::shared_ptr<OutStatementNode> outNode);
	void analyzeReturn(std::shared_ptr<ReturnStatementNode> returnNode);

	/*
	For anything expression related we need to return the type so we could type check everything
	*/
	TypeKind analyzeExpression(std::shared_ptr<ExpressionNode> expression);
	TypeKind analyzeBinaryExpression(std::shared_ptr<BinaryExpr> expression);
	TypeKind analyzeIdentifier(std::shared_ptr<IdentifierExpr> idExpr);
	TypeKind analyzeFunctionCall(std::shared_ptr<FunctionCallExpr> funcExpr);
	TypeKind analyzeNot(std::shared_ptr<NotExpr> notExpr);
};
