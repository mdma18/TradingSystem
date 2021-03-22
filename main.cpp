/* Copyright (c) 2021 */

#include "Program.hpp"

//=========================================================================================
Program::Program(std::string sFilename) : nInvalid(0), cDelimiter(' ') {
  ReadFile(sFilename);
  WriteToFile();
}
//=========================================================================================

//=========================================================================================
Program::~Program() {
  mCntMap.clear();
  vMessages.clear();
}
//=========================================================================================

// Read from a file line by line. Call Parser
//==============================================================================================
void Program::ReadFile(std::string sFile) {
  std::ifstream inFile(sFile);

  if (inFile.is_open()) {
    std::string sLine;
    std::getline(inFile, sLine);
    // Key/Value delimiter "0x01 = SOH"
    // cDelimiter = sLine[0];
    cDelimiter = sLine.at(9);
    ProcessMsg(sLine);
    // Iterate through every line
    while (std::getline(inFile, sLine)) {
      ProcessMsg(sLine);
      // break;
    }

  } else {
    std::cout << "Unable to open file";
  }
  inFile.close();
}
//==============================================================================================

// Determine whether a message is valid or invalid and store the valid one in the map.
//==============================================================================================
void Program::ProcessMsg(std::string sMsg) {
  std::string sKey, sValue;
  Message mMsg;
  int nQnt(0), nSide(0);
  float fPrc;
  while (!sMsg.empty()) {
    try {
      // Get key and rest of line after
      sKey = sMsg.substr(0, 3);
      sMsg = sMsg.substr(3);
      // Get value
      sValue = sMsg.substr(0, sMsg.find_first_of(cDelimiter));

      // State machine for parsing message line.
      if (sKey == PRICE) {
        // Price non-zero, less than 18 chars.
        fPrc = std::atof(sValue.c_str());
        mMsg.fPrice = (fPrc != 0 && sValue.size() < 20) ? fPrc : throw sValue;

      } else if (sKey == QUANTITY) {
        // Check for positive non-zero integer
        nQnt = std::atoi(sValue.c_str());
        mMsg.nQnt = (IsValid(sValue) && nQnt > 0) ? nQnt : throw sValue;

      } else if (sKey == SIDE) {
        // Check for either 1 or 2 (BUY/SELL)
        nSide = std::atoi(sValue.c_str());
        mMsg.nSide = (nSide == 1 || nSide == 2) ? nSide : throw sValue;

      } else if (sKey == SYMBOL) {
        // Check for correct Symbol, non-empty text only.
        mMsg.sSym = (IsValid(sValue) && sValue.size() > 0) ? sValue : throw sValue;
      }

      //  If struct is filled, store processed message.
      if (mMsg.fPrice > 0 && mMsg.nQnt && mMsg.nSide && !mMsg.sSym.empty()) {
        // Store Messages in vector, if necessary.
        (mMsg.nSide == 1) ? mCntMap[mMsg.sSym].first++ : mCntMap[mMsg.sSym].second++;
        vMessages.push_back(mMsg);
        break;
      } else {
        sMsg = sMsg.substr(sMsg.find_first_of(cDelimiter) + 1);
      }
    } catch (std::string sVal) {
      // Record number of invalid messages.
      nInvalid++;
      break;
    }
  }
}
//==============================================================================================

// Optional method, Print all contents of vector to a file.
//==============================================================================================
void Program::DumpVector() {
  std::ofstream outFile("PrettyMsgs.txt");

  for (auto &xElement : vMessages) {
    outFile << xElement.sSym << std::endl
            << std::fixed << std::setprecision(20) << xElement.fPrice << std::endl
            << xElement.nQnt << std::endl
            << xElement.nSide << std::endl;
  }
  outFile.close();
}
//==============================================================================================

// Write tally to a File.
//==============================================================================================
void Program::WriteToFile() {
  std::ofstream outFile("2021-03-12_summary.txt");
  int nBuy(0), nSell(0), nBoth(0);
  for (auto &zElement : mCntMap) {
    // If frequency count is greater than 1 then its a duplicate element
    // If the Symbol has been both bought/sold
    if (zElement.second.first && zElement.second.second) {
      nBoth += (zElement.second.first + zElement.second.second);
    } else if (zElement.second.first) {
      nBuy += zElement.second.first;
    } else if (zElement.second.second) {
      nSell += zElement.second.second;
    }
  }
  outFile << "BUYS: " << nBuy << std::endl
          << "SELLS: " << nSell << std::endl
          << "BOTH: " << nBoth << std::endl;
  outFile.close();
}
//==============================================================================================

// Sanitize a string, check for valid alphanumeric chars.
//==============================================================================================
bool Program::IsValid(std::string sVal) {
  bool bFlag(true);
  for (int i = 0; i < sVal.length(); i++) {
    if (!std::isalnum(sVal[i])) {
      bFlag = false;
      break;
    }
  }
  return bFlag;
}
//==============================================================================================

// Return number of invalid messages.
//==============================================================================================
int Program::GetInvalid() {
  return nInvalid;
}
//==============================================================================================

//==============================================================================================
int main() {
  Program pTest("messages.txt");
  std::cout << "Number of Invalid Messages: " << pTest.GetInvalid() << std::endl;
  return 0;
}
