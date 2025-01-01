#include "CodeGeneration.h"

CodeGeneration::CodeGeneration(const std::string& outputPath) : outputFile(outputPath), labels(0)
{
	if(!outputFile.is_open())
	{
		throw std::exception();
	}
}

void CodeGeneration::generate(std::unique_ptr<ProgramNode> head)
{
	
}

void CodeGeneration::emit(const std::string& data) 
{
	outputFile << data;
}

std::string CodeGeneration::createLabel()
{
	return "L" + std::to_string(++labels);
}

