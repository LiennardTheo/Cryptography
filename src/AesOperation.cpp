#include "Aes.hpp"

void Aes::subBytes(mat::Matrix<uint8_t, 4, 4>& matrix)
{
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            uint8_t index = matrix(i, j);
            uint8_t sBoxValue = _sBox[index];
            matrix(i, j) = sBoxValue;
        }
    }
}

void Aes::shiftRows(mat::Matrix<uint8_t, 4, 4>& matrix)
{
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < i; ++j) {
            uint8_t temp = matrix(i, 0);
            for (size_t k = 0; k < 3; ++k) {
                matrix(i, k) = matrix(i, k + 1);
            }
            matrix(i, 3) = temp;
        }
    }
}

uint8_t Aes::gfMul(uint8_t a, uint8_t b)
{
    uint8_t p = 0;
    uint8_t counter;
    uint8_t hi_bit_set;
    for (counter = 0; counter < 8; counter++) {
        if ((b & 1) == 1)
            p ^= a;
        hi_bit_set = (a & 0x80);
        a <<= 1;
        if (hi_bit_set == 0x80)
            a ^= 0x1b;
        b >>= 1;
    }
    return p;
}

void Aes::mixColumns(mat::Matrix<uint8_t, 4, 4>& matrix)
{
    mat::Matrix<uint8_t, 4, 4> tmp {
        {0x02, 0x03, 0x01, 0x01},
        {0x01, 0x02, 0x03, 0x01},
        {0x01, 0x01, 0x02, 0x03},
        {0x03, 0x01, 0x01, 0x02}
    };
    mat::Matrix<uint8_t, 4, 4> result {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0 ,0, 0}
    };
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j)
            result(i, j) = gfMul(tmp(i, 0), matrix(0, j)) ^ gfMul(tmp(i, 1), matrix(1, j)) ^ gfMul(tmp(i, 2), matrix(2, j)) ^ gfMul(tmp(i, 3), matrix(3, j));
    }
    matrix = result;
}

void Aes::addRoundKey(mat::Matrix<uint8_t, 4, 4>& matrix, size_t round)
{
    for (size_t i = 0; i < 4; ++i) {
        uint32_t key = _keySchedule[round * 4 + i];
        for (size_t j = 0; j < 4; ++j) {
            uint8_t value = key >> ((3 - j) * 8);
            matrix(j, i) = matrix(j, i) ^ value;
        }
    }
}

void Aes::invSubBytes(mat::Matrix<uint8_t, 4, 4>& matrix)
{
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            uint8_t index = matrix(i, j);
            uint8_t sBoxValue = _invSBox[index];
            matrix(i, j) = sBoxValue;
        }
    }
}

void Aes::invShiftRows(mat::Matrix<uint8_t, 4, 4>& matrix)
{
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < i; ++j) {
            uint8_t temp = matrix(i, 3);
            for (size_t k = 3; k > 0; --k) {
                matrix(i, k) = matrix(i, k - 1);
            }
            matrix(i, 0) = temp;
        }
    }
}

void Aes::invMixColumns(mat::Matrix<uint8_t, 4, 4>& matrix)
{
    mat::Matrix<uint8_t, 4, 4> tmp {
        {0x0e, 0x0b, 0x0d, 0x09},
        {0x09, 0x0e, 0x0b, 0x0d},
        {0x0d, 0x09, 0x0e, 0x0b},
        {0x0b, 0x0d, 0x09, 0x0e}
    };
    mat::Matrix<uint8_t, 4, 4> result {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0 ,0, 0},
        {0, 0, 0, 0}
    };
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j)
            result(i, j) = gfMul(tmp(i, 0), matrix(0, j)) ^ gfMul(tmp(i, 1), matrix(1, j)) ^ gfMul(tmp(i, 2), matrix(2, j)) ^ gfMul(tmp(i, 3), matrix(3, j));
    }
    matrix = result;
}

void Aes::invAddRoundKey(mat::Matrix<uint8_t, 4, 4>& matrix, size_t round)
{
    for (size_t i = 0; i < 4; ++i) {
        uint32_t key = _keySchedule[round * 4 + i];
        for (size_t j = 0; j < 4; ++j) {
            uint8_t value = key >> ((3 - j) * 8);
            matrix(j, i) = matrix(j, i) ^ value;
        }
    }
}