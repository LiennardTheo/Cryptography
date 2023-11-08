/*
** EPITECH PROJECT, 2023
** main
** File description:
** mathematics
*/

#include "my.hpp"

void xorMethod(std::string message, std::string key, int mode, bool block)
{
    std::cout << "XOR" << std::endl;
    std::cout << message << std::endl;
    std::cout << key << std::endl;
    std::cout << mode << std::endl;

    std::string result = "";
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
    std::cout << key << std::endl;
    std::cout << message << std::endl;

    if (std::string(argv[1]) == "-xor") {
        xorMethod(message, key, mode, block);
    } else if (std::string(argv[1]) == "-aes") {
        aesMethod(message, key, mode, block);
    } else if (std::string(argv[1]) == "-rsa") {
        rsaMethod(message, key, mode, block);
    } else {
        exit(1);
    }

    return 0;
}