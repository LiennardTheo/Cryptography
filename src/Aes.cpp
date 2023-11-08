#include "Aes.hpp"

Aes::Aes(std::string key)
{
}

std::string Aes::encrypt(std::string plainText)
{
    fillPlainText(plainText);
    return "";
}

std::string Aes::decrypt(std::string cipherText)
{
    return "";
}

void Aes::fillPlainText(std::string plainText)
{
    _plainText.clear();
    std::cout << plainText.size() << std::endl;
    for (size_t i = 0; i < plainText.size(); i += 16) {
        mat::Matrix<uint8_t, 4, 4> matrix;
        for (size_t j = 0; j < 16; ++j) {
            char c;
            if (i + j >= plainText.size())
                c = (i + 16) - plainText.size();
            else
                c = plainText[i + j];
            matrix(j % 4, j / 4) = c;
        }
        // matrix.print();
        // matrix.printB();
        _plainText.push_back(matrix);
    }
}