#pragma once
#include <fstream>
#include <unordered_map>
#include <string>
#include <limits>
#include "Token.h"
#include "../exceptions/lexer/LexerCouldntOpenFile.h"
#include "../exceptions/lexer/LexerUnclosedString.h"
#include "../exceptions/lexer/LexerUnknownSymbol.h"
#include "../exceptions/lexer/LexerFloatOutOfRange.h"
#include "../exceptions/lexer/LexerIntOutOfRange.h"
#include "../exceptions/lexer/LexerInvalidFloat.h"
#include "../exceptions/lexer/LexerInvalidInt.h"

class Lexer
{
public:
	Lexer(std::string path);
	~Lexer() = default;

	/*
	Finds the next token in the file
	Inputs: none
	Outputs: the next token
	*/
	Token getNextToken();

private:
	// The file containing the source code
	std::string m_filePath;

	// Current location in the file
	int m_currentLocation;

	// Current line number for error report
	int m_lineNumber;

	// Map to keep track of reservered ops and keywords
	std::unordered_map<std::string, TokenType> m_words;

	// Input-buffering variables (buffer pair technique)
	static const int BUFFER_SIZE = 1024;
	char m_buffer1[BUFFER_SIZE + 1];
	char m_buffer2[BUFFER_SIZE + 1];
	char* m_lexemeBegin;
	char* m_forward;

	// Previous string will be used if we switch buffer
	// This variable is used infrequently but ensures reliability
	std::string m_previous;
	
	/*
	Continue looping until the whitespace ends
	Inputs: none
	Outputs: Token containing the whitespaces
	*/
	Token whitespaceToken();
	
	/*
	Creates and returns the comment token
	Inputs: none
	Outputs: none
	*/
	Token commentToken();

	/*
	Check if the current token is possibly a double char token
	Inputs: current tag if interpreted as a single char
	Outputs: double char token or single char token depending on the result of the check
	*/
	Token possibleDoubleCharToken(TokenType currentTag);

	/*
	Creates and returns the string token
	Inputs: none
	Outputs: none
	*/
	Token stringToken();

	/*
	Creates and returns the number token
	Inputs: none
	Outputs: none
	*/
	Token numberToken();

	/*
	Creates and returns the real token
	Inputs: none
	Outputs: none
	*/
	Token realToken();

	/*
	Creates and returns the identifier token
	Inputs: none
	Outputs: none
	*/
	Token identifierToken();

	/*
	Reserves all words into the words map
	Input: none
	Outputs: none
	*/
	void initiateReserves();

	/*
	Reserves a single word in the word map
	Inputs: TokenType tag - tag, for reserve, std::string lexeme, the keyword for this tag
	Outputs: none
	*/
	void reserve(TokenType tag, const std::string& lexeme);

	/*
	Reads an input into a wanted buffer
	Inputs: the buffer to read into
	Outputs: none
	*/
	void readIntoBuffer(char* buffer);

	/*
	Advances the forward variables, handles buffer switching, handles file end
	Inputs: none
	Ouputs: bool - false if the input ends, true if the input continues
	*/
	bool advance();

	/*
	Checks if a token is in the m_words map
	Inputs: lexeme - the lexeme its searching for
	Outputs: returns the token if it was found, otherwise nullptr
	*/
	TokenType* getReservedWord(const std::string& lexeme) const;

	// Token creation function while also advancing in the input
	Token createTokenAndAdvance(TokenType tag);
	Token createTokenAndAdvance(TokenType tag, const std::string& lexeme);

	// Token creation functions - can't use template because enum
	Token createToken(TokenType tag) const;
	Token createToken(TokenType tag, const std::string& lexeme) const;
	Token createToken(int num) const;
	Token createToken(float real) const;
	Token createToken(bool boolean) const;
};

