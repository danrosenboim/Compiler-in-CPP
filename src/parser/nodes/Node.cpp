#include "Node.h"

Node::Node(int lineNumber) : m_lineNumber(lineNumber)
{
	
}

int Node::getLineNumber() const
{
	return m_lineNumber;
}
