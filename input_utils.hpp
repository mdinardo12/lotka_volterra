#ifndef INPUT_UTILS_HPP
#define INPUT_UTILS_HPP

#include <cstdlib>
#include <iostream>

template<typename T>
T read_param(const std::string& prompt)
{
  T value;
  std::cout << prompt;
  if (!(std::cin >> value)) {
    throw std::runtime_error("Invalid input");
  }
  return value;
}

#endif // INPUT_UTILS_HPP