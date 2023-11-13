#pragma once
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <iostream>

class Pgp {
    public:
        Pgp();
        ~Pgp();
        std::string pgpEncrypt(std::string plainText, std::string key);
        std::string pgpDecrypt(std::string cipherText, std::string key);

        std::string generateAesKey();

    protected:
    private:
        std::string _key;
};
