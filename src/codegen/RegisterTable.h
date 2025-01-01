#pragma once
#include <string>
#include <unordered_map>

// A table that keeps track of used registers
class RegisterTable
{
public:
	RegisterTable();
	
	/*
	 * Function that will
	 * Inputs: none
	 * Outputs: the allocated register
	 * */	
	std::string registerAllocate();

	/*
	 * Mark register as unused
	 * Inputs: register to mark
	 * Outputs: none
	 * */
	void regiserFree(std::string reg);

private:
	// Map that will contain all the registers that the assembly code could use
	std::unordered_map<std::string, bool> scratchRegisters;

	/*
	 * Function that adds all registers to the register map
	 * Inputs: none
	 * Outputs: none
	 * */
	void addRegisters();

};

