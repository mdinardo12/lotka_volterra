#ifndef INPUT_UTILS_HPP
#define INPUT_UTILS_HPP

#include <cstdlib>
#include <iostream>

// Template generico per leggere un input sicuro
template<typename T>
T read_param(const std::string& prompt, const std::string& error_msg)
{
  T value;
  std::cout << prompt;
  if (!(std::cin >> value)) {
    std::cout << "Error: " << error_msg << "\n";
    std::exit(EXIT_FAILURE);
  }
  return value;
}

#endif // INPUT_UTILS_HPP