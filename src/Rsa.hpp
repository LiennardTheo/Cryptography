/*
** EPITECH PROJECT, 2023
** rsa
** File description:
** tsa
*/

#pragma once
#include "my.hpp"
#include <numeric>

class Rsa {
    public:
        Rsa(std::string key);
        ~Rsa();
        void rsaGenerateKey(std::string p, std::string q);
        mpz_class rsaGcd(mpz_class a, mpz_class b);
        mpz_class findExponent(mpz_class lambdaN);
        std::string rsaEncrypt(std::string plainText);
        std::string rsaDecrypt(std::string cypherText);

    private:
        std::string _key;
};
