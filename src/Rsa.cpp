/*
** EPITECH PROJECT, 2023
** rsa cpp
** File description:
** cpp
*/

#include "Rsa.hpp"

std::string reverseHex(std::string hex)
{
    if (hex.length() % 2 != 0)
        hex = "0" + hex;

    std::string reversedHex;
    for (int i = hex.length() - 2; i >= 0; i -= 2) {
        reversedHex += hex.substr(i, 2);
    }
    return reversedHex;
}

Rsa::Rsa(std::string key)
{
    _key = key;
}

Rsa::~Rsa()
{
}

mpz_class Rsa::rsaGcd(mpz_class a, mpz_class b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

mpz_class Rsa::findExponent(mpz_class lambdaN)
{
    mpz_class e;
    if (lambdaN > 65537)
        e = 65537;
    else if (lambdaN % 2 == 0)
        e = lambdaN / 2;
    else
        e = lambdaN / 2 - 1;

    while (!(2 < e && e < lambdaN && rsaGcd(e, lambdaN) == 1)) {
        e += 2;
    }
    return e;
}

void Rsa::rsaGenerateKey(std::string p, std::string q)
{
    std::string pBigEndian = reverseHex(p);
    std::string qBigEndian = reverseHex(q);

    mpz_class pNum, qNum;
    mpz_set_str(pNum.get_mpz_t(), pBigEndian.c_str(), 16);
    mpz_set_str(qNum.get_mpz_t(), qBigEndian.c_str(), 16);

    mpz_class lambdaN;
    mpz_class pMinusOne = pNum - 1;
    mpz_class qMinusOne = qNum - 1;
    mpz_lcm(lambdaN.get_mpz_t(), pMinusOne.get_mpz_t(), qMinusOne.get_mpz_t());

    mpz_class e;
    e = findExponent(lambdaN);

    mpz_class n = pNum * qNum;

    std::cout << "public key: " << reverseHex(mpz_get_str(nullptr, 16, e.get_mpz_t())) << "-";
    std::cout << reverseHex(mpz_get_str(nullptr, 16, n.get_mpz_t())) << std::endl;

    mpz_class d;
    mpz_invert(d.get_mpz_t(), e.get_mpz_t(), lambdaN.get_mpz_t());

    std::cout << "private key: " << reverseHex(mpz_get_str(nullptr, 16, d.get_mpz_t())) << "-";
    std::cout << reverseHex(mpz_get_str(nullptr, 16, n.get_mpz_t())) << std::endl;
}

std::string Rsa::rsaEncrypt(std::string plainText)
{
    std::string key = _key;
    std::string e = reverseHex(key.substr(0, key.find("-")));
    std::string n = reverseHex(key.substr(key.find("-") + 1, key.length()));

    std::string message = reverseHex(plainText);

    mpz_class eNum, nNum, messageNum;
    mpz_set_str(eNum.get_mpz_t(), e.c_str(), 16);
    mpz_set_str(nNum.get_mpz_t(), n.c_str(), 16);
    mpz_set_str(messageNum.get_mpz_t(), message.c_str(), 16);

    mpz_class cipherNum;

    mpz_powm(cipherNum.get_mpz_t(), messageNum.get_mpz_t(), eNum.get_mpz_t(), nNum.get_mpz_t());

    std::string cipherText = mpz_get_str(nullptr, 16, cipherNum.get_mpz_t());

    return reverseHex(cipherText);
}

std::string Rsa::rsaDecrypt(std::string cipherText)
{
    std::string key = _key;
    std::string d = reverseHex(key.substr(0, key.find("-")));
    std::string n = reverseHex(key.substr(key.find("-") + 1, key.length()));


    std::string message = reverseHex(cipherText);

    mpz_class dNum, nNum, messageNum;
    mpz_set_str(dNum.get_mpz_t(), d.c_str(), 16);
    mpz_set_str(nNum.get_mpz_t(), n.c_str(), 16);
    mpz_set_str(messageNum.get_mpz_t(), message.c_str(), 16);

    mpz_class plainNum;
    mpz_powm(plainNum.get_mpz_t(), messageNum.get_mpz_t(), dNum.get_mpz_t(), nNum.get_mpz_t());

    std::string plainText = mpz_get_str(nullptr, 16, plainNum.get_mpz_t());
    return reverseHex(plainText);
}
