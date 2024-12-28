#include "CompilerException.h"

CompilerException::CompilerException(const std::string& msg, int lineNumber) : m_lineNumber(lineNumber)
{
	setMsg(msg);
}

void CompilerException::setMsg(const std::string& msg)
{
	m_msg = "Error at line " + std::to_string(m_lineNumber) + ": " + msg;
}

const char* CompilerException::what() const noexcept
{
	return m_msg.c_str();
}
