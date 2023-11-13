#include "Pgp.hpp"
#include "Aes.hpp"
#include "Rsa.hpp"

Pgp::Pgp()
{
}

Pgp::~Pgp()
{
}

std::string Pgp::generateAesKey()
{
    std::string key = "";
    for (int i = 0; i < 32; i++) {
        key += "0123456789abcdef"[rand() % 16];
    }
    return key;
}

std::string Pgp::pgpEncrypt(std::string plainText, std::string key)
{
    std::string aesKey = generateAesKey();
    Aes aes(aesKey);
    std::string cipherText = aes.encrypt(plainText, false);
    Rsa rsa(key);
    std::string cipherKey = rsa.rsaEncrypt(aesKey);
    return cipherKey + cipherText;
}

std::string Pgp::pgpDecrypt(std::string cipherText, std::string key)
{
    Rsa rsa(key);
    std::string aesKey = rsa.rsaDecrypt(cipherText.substr(0, 128));
    Aes aes(aesKey);
    std::string plainText = aes.decrypt(cipherText.substr(128), false);
    return plainText;
}