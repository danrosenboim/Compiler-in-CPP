#pragma once
#include <string>
#include <unordered_map>

class RegisterConverter {
private:
    static const std::unordered_map<std::string, std::pair<std::string, std::string>> registerMap;

public:
    static std::string convertRegisterTo32Bit(const std::string& reg);
    static std::string convertRegisterToByte(const std::string& reg64);
};