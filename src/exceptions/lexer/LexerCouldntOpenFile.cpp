#include "LexerCouldntOpenFile.h"

LexerCouldntOpenFile::LexerCouldntOpenFile(const std::string& fileName) : LexerException(std::string("File '") + fileName + "' could not be opened", 0)
{
}
