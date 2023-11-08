#pragma once

#include <string>
#include <vector>
#include <memory>

#include "../inc/Matrix.hpp"

class Aes {
    public:
        Aes(std::string key);
        std::string encrypt(std::string plainText);
        std::string decrypt(std::string cipherText);


        void fillPlainText(std::string plainText);
        ~Aes() = default;

    protected:
    private:
        std::string _key;

        std::vector<mat::Matrix<uint8_t, 4, 4>> _plainText;

};
