#pragma once
#include <string>
#include <unordered_map>

// A table that keeps track of used registers
class RegisterTable
{
public:
	RegisterTable();
	
	/*
	 * Function that will allocate a new register
	 * Inputs: none
	 * Outputs: the allocated register
	 * */	
	std::string registerAllocate();

	/*
	 * Mark register as unused
	 * Inputs: register to mark
	 * Outputs: none
	 * */
	void registerFree(std::string reg);

	/*
	 * Function that will allocate a new float register
	 * Inputs: none
	 * Outputs: a string containing the name of the allocated register
	 * */
	std::string floatRegisterAllocate();

	/*
	 * Mark register as unused
	 * Inputs: register to mark
	 * Outputs: none
	 * */
	void floatRegisterFree(std::string reg);

private:
	// Map that will contain all the registers that the assembly code could use
	std::unordered_map<std::string, bool> scratchRegisters;

	// Map that will contain all of the float registers
	std::unordered_map<std::string, bool> floatRegisters;

	/*
	 * Function that adds all registers to the register map
	 * Inputs: none
	 * Outputs: none
	 * */
	void addRegisters();

	/*
	 * Function that adds all the float registers to the map
	 * Inputs: none
	 * Outputs: none
	 * */
	void addFloatRegisters();
};

