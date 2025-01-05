#include "RegisterConverter.h"

// Define the static map for conversions (64-bit -> {32-bit, byte})
const std::unordered_map<std::string, std::pair<std::string, std::string>> RegisterConverter::registerMap = {
    {"%rax", {"%eax", "%al"}},
    {"%rbx", {"%ebx", "%bl"}},
    {"%rcx", {"%ecx", "%cl"}},
    {"%rdx", {"%edx", "%dl"}},
    {"%rsi", {"%esi", "%sil"}},
    {"%rdi", {"%edi", "%dil"}},
    {"%rbp", {"%ebp", "%bpl"}},
    {"%rsp", {"%esp", "%spl"}},
    {"%r8",  {"%r8d", "%r8b"}},
    {"%r9",  {"%r9d", "%r9b"}},
    {"%r10", {"%r10d", "%r10b"}},
    {"%r11", {"%r11d", "%r11b"}},
    {"%r12", {"%r12d", "%r12b"}},
    {"%r13", {"%r13d", "%r13b"}},
    {"%r14", {"%r14d", "%r14b"}},
    {"%r15", {"%r15d", "%r15b"}}
};

std::string RegisterConverter::convertRegisterTo32Bit(const std::string& reg)
{
    auto it = registerMap.find(reg);
    if (it != registerMap.end()) {
        return it->second.first;
    }
    throw std::exception();
}

std::string RegisterConverter::convertRegisterToByte(const std::string& reg64)
{
    auto it = registerMap.find(reg64);
    if (it != registerMap.end())
    {
        return it->second.second;
    }
    throw std::exception();
}