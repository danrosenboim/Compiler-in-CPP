#include "Lexer.h"

Lexer::Lexer(std::string path) : m_filePath(path), m_currentLocation(0), m_lineNumber(1),
	m_lexemeBegin(m_buffer1), m_forward(m_buffer1), m_previous("")
{
	initiateReserves();

	readIntoBuffer(m_buffer1);
}

Token Lexer::getNextToken()
{

	m_previous = "";
	m_lexemeBegin = m_forward;
	
	switch(*m_forward)
	{
	// If the current char is a whitespace continue until the end is reached
	case '\n':
		// Increase line number
		++m_lineNumber;
		return whitespaceToken();
	case ' ': return whitespaceToken();
	case '\t': return whitespaceToken();
	case '\r': return whitespaceToken();
	
	// Single-char tokens
	case '(': return createTokenAndAdvance(TokenType::LEFT_PAREN);
	case ')': return createTokenAndAdvance(TokenType::RIGHT_PAREN);
	case '{': return createTokenAndAdvance(TokenType::LEFT_BRACE);
	case '}': return createTokenAndAdvance(TokenType::RIGHT_BRACE);
	case '[': return createTokenAndAdvance(TokenType::LEFT_BRACKET);
	case ']': return createTokenAndAdvance(TokenType::RIGHT_BRACKET);
	case ';': return createTokenAndAdvance(TokenType::SEMICOLON);
	case ',': return createTokenAndAdvance(TokenType::COMMA);
	case '-': return createTokenAndAdvance(TokenType::MINUS);
	case '+': return createTokenAndAdvance(TokenType::PLUS);
	case '/': return createTokenAndAdvance(TokenType::SLASH);
	case '*': return createTokenAndAdvance(TokenType::STAR);
	
	// Possible double char Tokens
	case '!': return possibleDoubleCharToken(TokenType::NOT);
	case '=': return possibleDoubleCharToken(TokenType::EQUAL);
	case '<': return possibleDoubleCharToken(TokenType::LESS);
	case '>': return possibleDoubleCharToken(TokenType::GREATER);
	
	// String
	case '"': return stringToken();	

	// Comment
	case '#': return commentToken();
	
	// End of file
	case EOF: return createToken(TokenType::END_OF_FILE);

	default: break;
	}

	if(std::isdigit(*m_forward))
	{
		return numberToken();
	}

	if(std::isalpha(*m_forward) || *m_forward == '_')
	{
		return identifierToken();
	}

	throw LexerUnknownSymbol(*m_forward, m_lineNumber);
}

Token Lexer::whitespaceToken()
{
	advance();

	// Continue looping until we reach something that isnt a whitespace
	switch(*m_forward)
	{
	case '\n':
		++m_lineNumber;
		return whitespaceToken();
	case ' ': return whitespaceToken();
	case '\t': return whitespaceToken();
	case '\r': return whitespaceToken();
	default: return createToken(TokenType::WHITESPACE, m_previous + std::string(m_lexemeBegin, m_forward - m_lexemeBegin));
	}
}

Token Lexer::commentToken()
{
	// Keep advancing until a new line or end of file
	while(advance())
	{
		if(*m_forward == '\n')
		{
			++m_lineNumber;
			return createTokenAndAdvance(TokenType::COMMENT);
		}
	}

	return createToken(TokenType::END_OF_FILE);
}

Token Lexer::possibleDoubleCharToken(TokenType currentTag)
{
	advance();

	// Check if this token is a double char token
	if(*m_forward != '=')
	{
		// Length of 1 char
		return createToken(currentTag, m_previous + std::string(m_lexemeBegin, m_forward - m_lexemeBegin));
	}

	// Permanently advance	
	advance();

	std::string finalToken = m_previous + std::string(m_lexemeBegin, m_forward - m_lexemeBegin);

	return createToken(*getReservedWord(finalToken));
}

Token Lexer::stringToken()
{
	while(advance())
	{
		// Unclosed string
		if(*m_forward == '\n')
		{
			throw LexerUnclosedString(m_lineNumber);
		}
		else if(*m_forward == '"')
		{
			return createTokenAndAdvance(TokenType::TEXT, m_previous + std::string(m_lexemeBegin, m_forward - m_lexemeBegin) + '"');
		}
	}

	throw LexerUnclosedString(m_lineNumber);
}

Token Lexer::numberToken()
{
	advance();

	if(*m_forward == '.')
	{
		return realToken();
	}
	
	if(std::isdigit(*m_forward))
	{
		return numberToken();
	}

	if(std::isalpha(*m_forward))
	{
		throw LexerInvalidInt(m_lineNumber);
	}

	std::string currentNumber = m_previous + std::string(m_lexemeBegin, m_forward - m_lexemeBegin);

	// Make sure it is in int limits
	int value = 0;
	try
	{
		value = std::stoi(currentNumber);
	}
	catch(const std::out_of_range& e)
	{
		throw LexerIntOutOfRange(currentNumber, m_lineNumber);
	}

	return createToken(value);
}

Token Lexer::realToken()
{
	while(std::isdigit(*m_forward))
	{
		advance();
	}
	if(std::isalpha(*m_forward))
	{
		throw LexerInvalidFloat(m_lineNumber);
	}
	
	// Make sure the float is in float limits
	std::string currentNumber = m_previous + std::string(m_lexemeBegin, m_lexemeBegin - m_forward - 1);
	double temp = std::stod(currentNumber);

	if(temp > std::numeric_limits<float>::max() || temp < std::numeric_limits<float>::lowest())
	{
		throw LexerFloatOutOfRange(currentNumber, m_lineNumber);
	}

	return createToken(static_cast<float>(temp));
}

Token Lexer::identifierToken()
{
	advance();
	if(std::isalpha(*m_forward) || std::isdigit(*m_forward) || *m_forward == '_')
	{
		return identifierToken();
	}
	
	// Create token using the current string
	std::string currentString = m_previous + std::string(m_lexemeBegin, m_forward - m_lexemeBegin); 
	TokenType* tag = getReservedWord(currentString);
	

	return createToken((tag == nullptr ? TokenType::IDENTIFIER : *tag), currentString);
}

void Lexer::initiateReserves()
{
	// Ops and Single-Char tokens
	reserve(TokenType::EQUAL_EQUAL, "==");
	reserve(TokenType::GREATER_EQUAL, ">=");
	reserve(TokenType::LESS_EQUAL, "<=");
	reserve(TokenType::NOT_EQUAL, "!=");

	// Types
	reserve(TokenType::STRING, "text");
	reserve(TokenType::INT, "num");
	reserve(TokenType::FLOAT, "real");
	reserve(TokenType::BOOL, "bool");

	// Keywords
	reserve(TokenType::IF, "if");
	reserve(TokenType::THEN, "then");
	reserve(TokenType::ELSE, "else");
	reserve(TokenType::WHILE, "while");
	reserve(TokenType::TRUE, "true");
	reserve(TokenType::FALSE, "false");
	reserve(TokenType::FOR, "for");
	reserve(TokenType::UNTIL, "until");
	reserve(TokenType::FUNCTION, "function");
	reserve(TokenType::RETURN, "return");
	reserve(TokenType::OUT, "out");
	reserve(TokenType::IN, "in");
}

void Lexer::readIntoBuffer(char* buffer)
{
	std::ifstream file(m_filePath);

	// If file could not be found
	if(!file.is_open())
	{
		throw LexerCouldntOpenFile(m_filePath);
	}

	file.seekg(m_currentLocation);
	file.read(buffer, BUFFER_SIZE);
	
	// Check how many bytes we read
	int bytesRead = file.gcount();
	buffer[bytesRead] = EOF;
	m_currentLocation += bytesRead;
}

void Lexer::reserve(TokenType tag, const std::string& lexeme)
{
	m_words.insert(std::make_pair(lexeme, tag));
}

bool Lexer::advance()
{
	// Checking if we came to the end of a buffer or the file
	if(*++m_forward != EOF)
	{
		return true;
	}

	// If we reached the end of the buffer and not the end of the input
	// Determine the next buffer to fill up
	char* nextBuffer = nullptr;
	if(m_forward == m_buffer1 + BUFFER_SIZE + 1)
	{
		nextBuffer = m_buffer2;
	}
	else if(m_forward == m_buffer2 + BUFFER_SIZE + 1)
	{
		nextBuffer = m_buffer1;
	}
	else
	{
		// If the pointer isn't at the end of any one of the buffers then
		// we reached the end of the input
		return false;
	}

	// Fill up the new buffer
	// Save current lexeme into a variable
	m_previous += std::string(m_lexemeBegin, m_forward - m_lexemeBegin - 1);

	// Move into a buffer
	readIntoBuffer(nextBuffer);
	m_lexemeBegin = nextBuffer;
	m_forward = nextBuffer;

	return true;
}

TokenType* Lexer::getReservedWord(const std::string& lexeme) const
{
	// Search for the lexeme in the map
	auto it = m_words.find(lexeme);
	if(it != m_words.end())
	{
		// Return the value found
		return (TokenType*)&(it->second);
	}
	return nullptr;
}

Token Lexer::createTokenAndAdvance(TokenType tag)
{
	// Advance permanently
	advance();
	return Token(tag, m_lineNumber);
}

Token Lexer::createTokenAndAdvance(TokenType tag, const std::string& lexeme)
{
	// Advance permanently
	advance();
	return Token(tag, lexeme, m_lineNumber);
}

Token Lexer::createToken(TokenType tag) const
{
	return Token(tag, m_lineNumber);
}

Token Lexer::createToken(TokenType tag, const std::string& lexeme) const
{
	return Token(tag, lexeme, m_lineNumber);
}

Token Lexer::createToken(int num) const
{
	return Token(TokenType::NUMBER, num, m_lineNumber);
}

Token Lexer::createToken(float real) const
{
	return Token(TokenType::REAL, real, m_lineNumber);
}

Token Lexer::createToken(bool boolean) const
{
	return Token(TokenType::BOOLEAN, boolean, m_lineNumber);
}

