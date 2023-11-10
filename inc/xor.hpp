/*
** EPITECH PROJECT, 2023
** xor
** File description:
** xor func
*/

#pragma once
#include <vector>
#include <string>
#include <iostream>


std::vector<uint8_t> toVec(std::string str);
std::vector<uint8_t> operator*(std::vector<uint8_t> bytes1, std::vector<uint8_t> bytes2);
void outputHex(std::vector<uint8_t> bytes);
void xorMethod(std::string message, std::string key, bool block);