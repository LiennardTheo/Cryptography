/*
** EPITECH PROJECT, 2023
** main
** File description:
** mathematics
*/

#include "my.hpp"

std::string xorMethod(std::string message, std::string key, bool block)
{
    std::vector<uint8_t> bytes1, bytes2;
    for (int i = 0; i < message.size(); i += 2) {
        std::string byte_str = message.substr(i, 2);
        uint8_t byte = (uint8_t) strtol(byte_str.c_str(), NULL, 16);
        bytes1.push_back(byte);
    }
    for (int i = 0; i < key.size(); i += 2) {
        std::string byte_str = key.substr(i, 2);
        uint8_t byte = (uint8_t) strtol(byte_str.c_str(), NULL, 16);
        bytes2.push_back(byte);
    }

    std::vector<uint8_t> result_bytes;
    for (int i = 0; i < bytes1.size(); i++) {
        uint8_t result_byte = bytes1[i] ^ bytes2[i % bytes2.size()];
        result_bytes.push_back(result_byte);
    }

    std::string hex_result = "";
    for (int i = 0; i < result_bytes.size(); i++) {
        char hex_byte[3];
        std::sprintf(hex_byte, "%02x", result_bytes[i]);
        hex_result += hex_byte;
    }

    std::cout << hex_result << std::endl;
    return hex_result;
}

void aesMethod(std::string message, std::string key, int mode, bool block)
{
}

void rsaMethod(std::string message, std::string key, int mode, bool block)
{
}

int main(int argc, char **argv) {
    if (argc < 4) {
        exit(1);
    }
    std::string message;
    std::getline(std::cin, message);

    int mode = 0;
    bool block = false;
    if (std::string(argv[2]) == "-c") {
        mode = 1;
    } else if (std::string(argv[2]) == "-d") {
        mode = 2;
    }

    if (mode == 0) {
        exit(1);
    }

    if (std::string(argv[3]) == "-d")
        block = true;

    std::string key = argv[argc - 1];

    if (std::string(argv[1]) == "-xor") {
        xorMethod(message, key, block);
    } else if (std::string(argv[1]) == "-aes") {
        aesMethod(message, key, mode, block);
    } else if (std::string(argv[1]) == "-rsa") {
        rsaMethod(message, key, mode, block);
    } else {
        exit(1);
    }

    return 0;
}