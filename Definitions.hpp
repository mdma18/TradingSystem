/**
 * @file Definitions.hpp
 * @author Amdadullah Md (mamdadullah18@gmail.com)
 * @brief Header file to implement global definitions
 * accessible by any class.
 * @version 0.1
 * @date 2021-03-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef DEFINITIONS_HPP_
#define DEFINITIONS_HPP_

/* Standard Libraries */
#include <stdio.h>
/* STD::OUT */
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
/* Constant definitions */
constexpr auto PRICE = "31=";
constexpr auto QUANTITY = "32=";
constexpr auto SIDE = "54=";
constexpr auto SYMBOL = "55=";

// Efficient if there are more Airports
struct Message {
  float fPrice;      // Price of symbol
  int nQnt;          // Quantity of symbol
  int nSide;         // 1: BUY - 2: SELL
  std::string sSym;  // Symbol name
};

#endif  // DEFINITIONS_HPP_
