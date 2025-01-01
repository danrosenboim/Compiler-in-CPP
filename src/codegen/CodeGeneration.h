#pragma once
#include <memory>
#include <fstream>
#include "RegisterTable.h"
#include "../parser/nodes/ProgramNode.h"

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
	std::ifstream outputFile;

	// This variable will keep track of the temporary labels that we generate
	int labels;

	/* Function that writes info to a file*/
	void emit(const std::string& data);

	/*
	 * Increases the global label counter and returns the new labels name
	 * Inputs: none
	 * Outputs: new label
	 * */
	std::string createLabel();
};
