#include "Token.h"

Token::Token(TokenType tag, int lineNumber) : m_tag(tag), m_lineNumber(lineNumber), m_value(0) {}

Token::Token(TokenType tag, std::string s, int lineNumber) : m_tag(tag), m_lineNumber(lineNumber), m_value(s) {}

Token::Token(TokenType tag, int i, int lineNumber) : m_tag(tag), m_lineNumber(lineNumber), m_value(i) {}

Token::Token(TokenType tag, float f, int lineNumber) : m_tag(tag), m_lineNumber(lineNumber), m_value(f) {}

Token::Token(TokenType tag, bool b, int lineNumber) : m_tag(tag), m_lineNumber(lineNumber), m_value(b) {}

Token::Token(const Token& other) : m_tag(other.m_tag), m_lineNumber(other.m_lineNumber), m_value(other.m_value) {}

TokenType Token::getTag() const
{
    return m_tag;
}

std::string Token::getLexeme() const
{
    return std::get<std::string>(m_value);
}

int Token::getNumber() const
{
    return std::get<int>(m_value);
}

float Token::getReal() const
{
    return std::get<float>(m_value);
}

bool Token::getBool() const
{
    return std::get<bool>(m_value);
}

std::string Token::typeToString(TokenType type)
{
    switch (type)
    {
        case TokenType::LEFT_PAREN: return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case TokenType::LEFT_BRACE: return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE: return "RIGHT_BRACE";
        case TokenType::LEFT_BRACKET: return "LEFT_BRACKET";
        case TokenType::RIGHT_BRACKET: return "RIGHT_BRACKET";
        case TokenType::COMMA: return "COMMA";
        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::MINUS: return "MINUS";
        case TokenType::PLUS: return "PLUS";
        case TokenType::SLASH: return "SLASH";
        case TokenType::STAR: return "STAR";
        case TokenType::EQUAL: return "EQUAL";
        case TokenType::EQUAL_EQUAL: return "EQUAL_EQUAL";
        case TokenType::GREATER: return "GREATER";
        case TokenType::GREATER_EQUAL: return "GREATER_EQUAL";
        case TokenType::LESS: return "LESS";
        case TokenType::LESS_EQUAL: return "LESS_EQUAL";
        case TokenType::NOT: return "NOT";
        case TokenType::NOT_EQUAL: return "NOT_EQUAL";
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::TEXT: return "TEXT";
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::REAL: return "REAL";
        case TokenType::BOOLEAN: return "BOOLEAN";
        case TokenType::STRING: return "STRING";
        case TokenType::INT: return "INT";
        case TokenType::FLOAT: return "FLOAT";
        case TokenType::BOOL: return "BOOL";
        case TokenType::IF: return "IF";
        case TokenType::THEN: return "THEN";
        case TokenType::ELSE: return "ELSE";
        case TokenType::WHILE: return "WHILE";
        case TokenType::TRUE: return "TRUE";
        case TokenType::FALSE: return "FALSE";
        case TokenType::FOR: return "FOR";
	case TokenType::UNTIL: return "UNTIL";
        case TokenType::RETURN: return "RETURN";
	case TokenType::FUNCTION: return "FUNCTION";
        case TokenType::OUT: return "OUT";
	case TokenType::IN: return "IN";
	case TokenType::COMMENT: return "COMMENT";
	case TokenType::WHITESPACE: return "WHITESPACE";
        case TokenType::END_OF_FILE: return "END_OF_FILE";
        default: return "UNKNOWN";
    }
}

std::ostream& operator<<(std::ostream& os, const Token& token)
{
    os << Token::typeToString(token.getTag());
    return os;
}
