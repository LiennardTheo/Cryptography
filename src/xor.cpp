/*
** EPITECH PROJECT, 2023
** asdq
** File description:
** qsd
*/

#include "my.hpp"

std::vector<uint8_t> toVec(std::string str)
{
    std::vector<uint8_t> result;
    for (int i = 0; i < str.size(); i += 2) {
        std::string byte_str = str.substr(i, 2);
        uint8_t byte = (uint8_t) std::stoll(byte_str, nullptr, 16);
        result.push_back(byte);
    }
    return result;
}

std::vector<uint8_t> operator*(std::vector<uint8_t> bytes1, std::vector<uint8_t> bytes2)
{
    std::vector<uint8_t> result(bytes1.size() + bytes2.size());
    for (int i = 0 ; i < bytes1.size() ; i++) {
        uint8_t carry = 0;
        for (int j = 0 ; j < bytes2.size() || carry > 0 ; j++) {
            int32_t product = result[i + j] + bytes1[i] * (j < bytes2.size() ? bytes2[j] : 0) + carry;
            result[i + j] = product & 0xff;
            carry = product >> 8;
        }
    }

    return result;
}

void outputHex(std::vector<uint8_t> bytes)
{
    std::string hex_result = "";
    for (int i = 0; i < bytes.size(); i++) {
        char hex_byte[3];
        std::sprintf(hex_byte, "%02x", bytes[i]);
        hex_result += hex_byte;
    }

    std::cout << hex_result;
}

void xorMethod(std::string message, std::string key, bool block)
{
    std::vector<uint8_t> bytes1 = toVec(message);
    std::vector<uint8_t> bytes2 = toVec(key);

    std::vector<uint8_t> result_bytes;
    for (int i = 0; i < bytes1.size(); i++) {
        uint8_t result_byte = bytes1[i] ^ bytes2[i % bytes2.size()];
        result_bytes.push_back(result_byte);
    }
    outputHex(result_bytes);
}
