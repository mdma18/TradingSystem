/**
 * @file Program.hpp
 * @author your name (mamdadullah18@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-03-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef PROGRAM_HPP_
#define PROGRAM_HPP_

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "Definitions.hpp"
class Program {
 public:
  explicit Program(std::string sFilename);
  virtual ~Program();

  /* Public Methods */
  void DumpVector();
  int GetInvalid();

 private:
  /* Private Methods */
  void ReadFile(std::string sFile);
  void ProcessMsg(std::string sMsg);
  void WriteToFile();
  bool IsValid(std::string sVal);

 private:
  /* Defined to prevent copying */
  Program(const Program& other);
  Program& operator=(const Program& other);

  /* Attributes */
  std::vector<Message> vMessages;                      // Map to hold valid FIX messages.
  std::map<std::string, std::pair<int, int>> mCntMap;  // Map to hold count of items for SIDE enum, first -> BUYS, second -> SELLS.
  int nInvalid;                                        // Counter for invalid messages.
  char cDelimiter;                                     // Stores delimiting char between key/value pairs.
};
#endif  // PROGRAM_HPP_
