#include "Compiler.h"

Compiler::Compiler(const std::string& filePath) : m_filePath(filePath), scanner(std::make_shared<Lexer>(filePath)), parser(std::make_unique<Parser>(scanner))
{ }


