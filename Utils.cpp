#include "Utils.h"
#include <iostream>
#include <string>
#include <cctype>

int Utils::checkInputIsNumber() {
  std::string input;
  std::string digits;
  std::getline(std::cin, input);

  for (char c : input) {
    if (std::isdigit(static_cast<unsigned char>(c))) {
      digits += c;
    }
  }

  if (digits.empty() || digits != input) {
    std::cout << "ERROR: ingrese solo numeros" << std::endl;
    return -1;
  }
  int number = std::stoi(digits);
  return number;
}
