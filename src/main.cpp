/*
** EPITECH PROJECT, 2023
** main
** File description:
** mathematics
*/

#include "my.hpp"
#include "Aes.hpp"
#include "Rsa.hpp"
#include "Pgp.hpp"

void aesMethod(std::string message, std::string key, int mode, bool block)
{
    std::cout << block << std::endl;
    if (mode == 1) {
        Aes aes(key);
        std::string cipherText = aes.encrypt(message, block);
        std::cout << cipherText << std::endl;
    } else if (mode == 2) {
        Aes aes(key);
        std::string plainText = aes.decrypt(message, block);
        std::cout << plainText << std::endl;
    }
}

void rsaMethod(std::string message, std::string key, int mode)
{
    if (mode == 1) {
        Rsa rsa(key);
        std::string cipherText = rsa.rsaEncrypt(message);
        std::cout << cipherText << std::endl;
    } else if (mode == 2) {
        Rsa rsa(key);
        std::string plainText = rsa.rsaDecrypt(message);
        std::cout << plainText << std::endl;
    }
}

void pgpMethod(std::string message, std::string key, int mode)
{
    if (mode == 1) {
        Pgp pgp;
        std::string cipherText = pgp.pgpEncrypt(message, key);
        std::cout << cipherText << std::endl;
    } else if (mode == 2) {
        Pgp pgp;
        std::string plainText = pgp.pgpDecrypt(message, key);
        std::cout << plainText << std::endl;
    }
}

int main(int argc, char **argv) {
    if (argc < 4) {
        exit(1);
    }

    int mode = 0;
    bool block = false;
    if (std::string(argv[2]) == "-c") {
        mode = 1;
    } else if (std::string(argv[2]) == "-d") {
        mode = 2;
    } else if (std::string(argv[2])==  "-g")
        mode = 3;

    if (std::string(argv[3]) == "-b")
        block = true;

    std::string key = argv[argc - 1];

    if (std::string(argv[1]) == "-xor") {
        std::string message;
        std::getline(std::cin, message);
        xorMethod(message, key, block);
    } else if (std::string(argv[1]) == "-aes") {
        std::string message;
        std::getline(std::cin, message);
        aesMethod(message, key, mode, block);
    } else if (std::string(argv[1]) == "-rsa") {
        if (mode == 3) {
            Rsa rsa(key);
            rsa.rsaGenerateKey(argv[argc - 2], argv[argc - 1]);
            return 0;
        }
        std::string message;
        std::getline(std::cin, message);
        rsaMethod(message, key, mode);
    } else if (std::string(argv[1]) == "-pgp") {
        std::string message;
        std::getline(std::cin, message);
        pgpMethod(message, key, mode);
    } else {
        exit(1);
    }

    return 0;
}

// 4b1da73924978f2e9c1f04170e46820d648edbee12ccf4d4462af89b080c86e1
// bb3ca1e126f7c8751bd81bc8daa226494efb3d128f72ed9f6cacbe96e14166cb