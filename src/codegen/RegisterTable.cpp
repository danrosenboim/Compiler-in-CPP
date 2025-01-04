#include "RegisterTable.h"

RegisterTable::RegisterTable()
{
	addRegisters();
}

std::string RegisterTable::registerAllocate()
{
	auto reg = std::find_if(scratchRegisters.begin(), scratchRegisters.end(), [](auto pairs){ return !pairs.second; });

	if(reg == scratchRegisters.end())
	{
		// ERROR
		throw std::exception();
	}

	reg->second = true;

	return reg->first;
}

void RegisterTable::registerFree(std::string reg)
{
	// Free float register
	if (reg.size() >= 2 && reg[1] == 'x')
	{
		floatRegisterFree(reg);
		return;
	}

	// Free GP register
	auto it = scratchRegisters.find(reg);
	if (it == scratchRegisters.end())
	{
		throw std::exception();
	}
	
	it->second = false;
}

std::string RegisterTable::floatRegisterAllocate()
{
	auto reg = std::find_if(floatRegisters.begin(), floatRegisters.end(), [](auto pairs) { return !pairs.second; });

	if (reg == floatRegisters.end())
	{
		// ERROR
		throw std::exception();
	}

	reg->second = true;

	return reg->first;
}

void RegisterTable::floatRegisterFree(std::string reg)
{
	auto it = scratchRegisters.find(reg);
	if (it == scratchRegisters.end())
	{
		throw std::exception();
	}

	it->second = false;
}

void RegisterTable::addRegisters()
{
	// Adding all the registers that could be used
	scratchRegisters.insert(std::make_pair<std::string, bool>("%rbx", false));
	scratchRegisters.insert(std::make_pair<std::string, bool>("%r10", false));
	scratchRegisters.insert(std::make_pair<std::string, bool>("%r11", false));
	scratchRegisters.insert(std::make_pair<std::string, bool>("%r12", false));
	scratchRegisters.insert(std::make_pair<std::string, bool>("%r13", false));
	scratchRegisters.insert(std::make_pair<std::string, bool>("%r14", false));
	scratchRegisters.insert(std::make_pair<std::string, bool>("%r15", false));
}

void RegisterTable::addFloatRegisters()
{
	// Adding all the xmm registers that could be used
	scratchRegisters.insert(std::make_pair("%xmm0", false));
	scratchRegisters.insert(std::make_pair("%xmm1", false));
	scratchRegisters.insert(std::make_pair("%xmm2", false));
	scratchRegisters.insert(std::make_pair("%xmm3", false));
	scratchRegisters.insert(std::make_pair("%xmm4", false));
	scratchRegisters.insert(std::make_pair("%xmm5", false));
	scratchRegisters.insert(std::make_pair("%xmm6", false));
	scratchRegisters.insert(std::make_pair("%xmm7", false));
	scratchRegisters.insert(std::make_pair("%xmm8", false));
	scratchRegisters.insert(std::make_pair("%xmm9", false));
	scratchRegisters.insert(std::make_pair("%xmm10", false));
	scratchRegisters.insert(std::make_pair("%xmm11", false));
	scratchRegisters.insert(std::make_pair("%xmm12", false));
	scratchRegisters.insert(std::make_pair("%xmm13", false));
	scratchRegisters.insert(std::make_pair("%xmm14", false));
	scratchRegisters.insert(std::make_pair("%xmm15", false));

}
