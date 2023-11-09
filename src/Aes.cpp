#include "Aes.hpp"

Aes::Aes(std::string key)
{
    _key = key;
}

std::string Aes::encrypt(std::string plainText, bool block)
{
    fillPlainText(plainText);
    fillKeySchedule();
    for (auto& matrix : _plainText) {
        encryptMatrix(matrix);
    }
    std::stringstream ss;
    if (block) {
        ss << matrixToString(_plainText[0]);
    } else {
        for (auto& matrix : _plainText) {
            ss << matrixToString(matrix);
        }
    }
    return ss.str();
}

std::string Aes::decrypt(std::string cipherText, bool block)
{
    fillCipherText(cipherText);
    fillKeySchedule();
    for (auto& matrix : _cipherText) {
        decryptMatrix(matrix);
    }
    std::stringstream ss;
    if (block) {
        ss << matrixToString(_plainText[0]);
    } else {
        for (auto& matrix : _cipherText) {
            ss << matrixToString(matrix);
        }
    }
    return ss.str();
}

void Aes::encryptMatrix(mat::Matrix<uint8_t, 4, 4>& matrix)
{
    addRoundKey(matrix, 0);
    for (int i = 1; i < _keySchedule.size() / 4; ++i) {
        subBytes(matrix);
        shiftRows(matrix);
        if (i != (_keySchedule.size() - 1) / 4)
            mixColumns(matrix);
        addRoundKey(matrix, i);
    }
}

void Aes::decryptMatrix(mat::Matrix<uint8_t, 4, 4>& matrix)
{
    addRoundKey(matrix, 10);
    for (int i = 9; i >= 0; --i) {
        invShiftRows(matrix);
        invSubBytes(matrix);
        addRoundKey(matrix, i);
        if (i != 0)
            invMixColumns(matrix);
    }
}

void Aes::fillCipherText(std::string cipherText)
{
    _cipherText.clear();
    for (size_t i = 0; i < cipherText.size(); i += 32) {
        mat::Matrix<uint8_t, 4, 4> matrix;
        for (size_t j = 0; j < 16; ++j) {
            uint8_t c;
            if (i + (j * 2) >= (cipherText.size()))
                c = (i + 16) - (cipherText.size());
            else
                c = std::stoll(cipherText.substr(i + (j * 2), 2), nullptr, 16);
            matrix(j % 4, j / 4) = c;
        }
        _cipherText.push_back(matrix);
    }
}

std::string Aes::matrixToString(mat::Matrix<uint8_t, 4, 4>& matrix)
{
    std::stringstream ss;
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            if (matrix(j, i) < 16)
                ss << "0";
            ss << std::hex << (int)matrix(j, i);
        }
    }
    return ss.str();
}

void Aes::fillPlainText(std::string plainText)
{
    _plainText.clear();
    for (size_t i = 0; i < plainText.size(); i += 32) {
        mat::Matrix<uint8_t, 4, 4> matrix;
        for (size_t j = 0; j < 16; ++j) {
            uint8_t c;
            if (i + (j * 2) >= (plainText.size()))
                c = 0;
            else
                c = std::stoll(plainText.substr(i + (j * 2), 2), nullptr, 16);
            matrix(j % 4, j / 4) = c;
        }
        // matrix.printB();
        // std::cout << std::endl;
        _plainText.push_back(matrix);
    }
}

void Aes::fillKeySchedule()
{
    std::vector<uint32_t> keySchedule = std::vector<uint32_t>(44);
    std::vector<uint32_t> rcon = {0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x1B000000, 0x36000000};
    for (size_t i = 0; i < 4; ++i) {
        std::string sub = _key.substr(i * 8, 8);
        uint32_t value = std::stoul(sub, nullptr, 16);
        keySchedule[i] = value;
    }

    for (size_t i = 4; i < 44; ++i) {
        uint32_t temp = keySchedule[i - 1];
        if (i % 4 == 0) {
            uint32_t rotWord = (temp << 8) | (temp >> 24);
            uint32_t subWord = 0;
            for (size_t j = 0; j < 4; ++j) {
                uint8_t index = rotWord >> (j * 8);
                uint8_t sBoxValue = _sBox[index];
                subWord |= sBoxValue << (j * 8);
            }
            temp = subWord ^ rcon[(i / 4) - 1];
        }
        keySchedule[i] = keySchedule[i - 4] ^ temp;
    }
    _keySchedule = keySchedule;
}
