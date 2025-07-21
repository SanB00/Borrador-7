#include "Utils.h"
#include <cctype>
#include <iostream>
#include <string>

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
    std::cerr << "ERROR: ingrese solo numeros" << std::endl;
    return -1;
  }
  int numero = std::stoi(digits);
  return numero;
}

float Utils::checkInputIsFloat() {
  std::string entrada;
  std::getline(std::cin, entrada);
  try {
    if (entrada.empty()) {
      throw std::runtime_error("ERROR: Este ingreso esta en blanco");
    }

    for (char c : entrada) {
      if (!isdigit(c)) {
        if (c != '.') {
          throw std::runtime_error("ERROR: Solo se permite nros y punto para decimales");
        }
      }
    }

    float numero = std::stof(entrada);
    return numero;
  } catch (const std::exception &e) {
    std::cerr << "ERROR: ingrese solo numeros decimales o enteros - " << e.what() << std::endl;
  }
}