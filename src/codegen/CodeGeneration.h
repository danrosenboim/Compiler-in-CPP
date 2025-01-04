#pragma once
// REMOVE AFTER TEMP USE
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include "RegisterTable.h"
#include "ScopeManager.h"
#include "../parser/nodes/ProgramNode.h"
#include "../parser/nodes/AssignmentStatementNode.h"
#include "../parser/nodes/BinaryExpr.h"
#include "../parser/nodes/NumberExpr.h"
#include "../parser/nodes/RealExpr.h"
#include "../parser/nodes/StringExpr.h"
#include "../parser/nodes/BoolExpr.h"
#include "../parser/nodes/NotExpr.h"
#include "../parser/nodes/IdentifierExpr.h"
#include "../parser/nodes/FunctionCallExpr.h"
#include "../parser/nodes/DeclarationStatementNode.h"
#include "../parser/nodes/ForStatementNode.h"
#include "../parser/nodes/InStatementNode.h"
#include "../parser/nodes/OutStatementNode.h"
#include "../parser/nodes/FunctionNode.h"
#include "../parser/nodes/ReturnStatementNode.h"
#include "../exceptions/CompilerException.h"

class CodeGeneration
{
public:
	CodeGeneration(const std::string& outputPath);
	
	/*
	 * Function that will initiate the code generation sequence
	 * Inputs: Program AST for code generation
	 * Outputs: none
	 * */
	void generate(std::unique_ptr<ProgramNode> head);

private:
	// Stores the output file stream
	std::ofstream outputFile;

	// This variable will keep track of the temporary labels that we generate
	int labels;

	// Keeps track of available registers
	RegisterTable regTable;

	// Keeps track of the scopes we enter or leave
	ScopeManager scopeManager;

	// Map to store function ending labels
	std::unordered_map<std::string, std::string> functionEndings;

	// Maps string contents to its hidden label
	std::unordered_map<std::string, std::string> stringLiterals;

	/* Function that writes info to a file*/
	void emit(const std::string& data);

	/*
	Adds a new string literal to the map
	Inputs: new string literal
	Outputs: the new label created or if it already existed then the already created label
	*/
	std::string addStringLiteral(const std::string& str);

	/*
	Generates all the string literals in the .rodata section
	Inputs: none
	Outputs: none
	*/
	void generateStringLiterals();

	/*
	 * Increases the global label counter and returns the new labels name
	 * Inputs: none
	 * Outputs: new label
	 * */
	std::string createLabel();

	/*
	Function that converts float to IEEE 754 representation
	Inputs: a float to convert to its representation
	Outputs: an int containting the float in IEEE 754 repressentation
	*/
	uint32_t floatToIEEE(float value);

	// Generating functions for each item
	void generateGlobal(std::shared_ptr<Symbol> symbol);
	void generateFunction(std::shared_ptr<FunctionNode> func);
	void generateBlock(std::shared_ptr<BlockNode> block, bool enterScope);
	void generateStatement(std::shared_ptr<StatementNode> statement);

	// Statement functions
	void generateAssignment(std::shared_ptr<AssignmentStatementNode> assignment);
	void generateDeclaration(std::shared_ptr<DeclarationStatementNode> decl);
	void generateForStatement(std::shared_ptr<ForStatementNode> forNode);
	void generateIfStatement(std::shared_ptr<IfStatementNode> ifNode);
	void generateInStatement(std::shared_ptr<InStatementNode> inNode);
	void generateOutStatement(std::shared_ptr<OutStatementNode> outNode);
	void generateReturn(std::shared_ptr<ReturnStatementNode> returnStmt);

	// Expression Generation Functions
	std::string generateExpression(std::shared_ptr<ExpressionNode> expr);
	std::string generateBinaryExpr(std::shared_ptr<BinaryExpr> binExpr);
	std::string generateFunctionCall(std::shared_ptr<FunctionCallExpr> funcExpr);
};
