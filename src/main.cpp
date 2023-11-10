/*
** EPITECH PROJECT, 2023
** main
** File description:
** mathematics
*/

#include "my.hpp"
#include "Aes.hpp"

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

void rsaMethod(std::string message, std::string key, int mode, bool block)
{
}

// std::vector<uint8_t> gcd(std::vector<uint8_t> a, std::vector<uint8_t> b)
// {
//     if (a.size() == 0)
//         return b;
//     return gcd(b % a, a);
// }

// std::vector<uint8_t> gcdExtended(std::vector<uint8_t> a, std::vector<uint8_t> b, std::vector<uint8_t> *x, std::vector<uint8_t> *y)
// {
//     //cas de base -> si a = 0 -> b = GCD / x = 0 et y = 1 pour stopper toutes les recursions §§ attention inversé
//     if (a.size() == 0) {
//         *x = {0};
//         *y = {1};
//         return b;
//     }

//     std::vector<uint8_t> x1, y1;
//     std::vector<uint8_t> gcd = gcdExtended(b % a, a, &x1, &y1);

//     *x = y1 - (b / a) * x1;
//     *y = x1;

//     return gcd;
// }

void rsaGenerateKey(std::string p, std::string q)
{
//     std::vector<uint8_t> pBytes = toVec(p);
//     std::vector<uint8_t> qBytes = toVec(q);
//     std::vector<uint8_t> e = {0x01, 0x00, 0x01};

//     std::vector<uint8_t> n = pBytes * qBytes;
//     // outputHex(n);
//     std::cout << "public key: ";
//     outputHex(e);
//     std::cout << "-";
//     outputHex(n);
//     std::cout << std::endl;

//     // std::vector<uint8_t> totient = (pBytes - 1) * (qBytes - 1);
//     // outputHex(totient);

//     std::vector<uint8_t> x, y;
//     // std::vector<uint8_t> d = gcdExtended(e, totient, &x, &y);
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

    if (std::string(argv[3]) == "-b")
        block = true;

    std::string key = argv[argc - 1];

    if (std::string(argv[1]) == "-xor") {
        xorMethod(message, key, block);
    } else if (std::string(argv[1]) == "-aes") {
        aesMethod(message, key, mode, block);
    } else if (std::string(argv[1]) == "-rsa") {
        if (std::string(argv[2]) == "-g") {
            rsaGenerateKey(argv[3], argv[4]);
        } else {
            rsaMethod(message, key, mode, block);
        }
    } else {
        exit(1);
    }

    return 0;
}

// 4b1da73924978f2e9c1f04170e46820d648edbee12ccf4d4462af89b080c86e1
// bb3ca1e126f7c8751bd81bc8daa226494efb3d128f72ed9f6cacbe96e14166cb