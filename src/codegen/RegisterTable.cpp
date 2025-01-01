#include "RegisterTable.h"

RegisterTable::RegisterTable()
{
	addRegister();
}

std::string RegisterTable::registerAllocate()
{
	auto reg = std::find_if(scratchRegisters.begin(), scratchRegisters.end(), [](auto pairs){ return !pairs.second; });

	if(reg == scratchRegisters.end())
	{
		// ERROR
		throw std::exception();
	}

	return reg;
}

void RegisterTable::addRegisters()
{
	// Adding all the variables that could be used
	scratchRegisters.insert(std::make_pair<std::string, bool>("%rbx", false));
	scratchRegisters.insert(std::make_pair<std::string, bool>("%r10", false));
	scratchRegisters.insert(std::make_pair<std::string, bool>("%r11", false));
	scratchRegisters.insert(std::make_pair<std::string, bool>("%r12", false));
	scratchRegisters.insert(std::make_pair<std::string, bool>("%r13", false));
	scratchRegisters.insert(std::make_pair<std::string, bool>("%r14", false));
	scratchRegisters.insert(std::make_pair<std::string, bool>("%r15", false));
}
