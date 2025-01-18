#pragma once
#include <exception>
#include <string>

// Base for exception inheritence
class CompilerException : public std::exception
{	
public:
	CompilerException(const std::string& msg, int lineNumber);
	
	virtual const char* what() const noexcept override;
private:
	void setMsg(const std::string& msg);

	std::string m_msg;
	int m_lineNumber;
};
