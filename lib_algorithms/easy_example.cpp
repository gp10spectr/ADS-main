// Copyright 2024 Khaferl Pavel

#include "lib_algorithms/easy_example.h"
#include <stdexcept>
#include "lib_stack_on_mass/stack_on_mass.h"

float division(int a, int b) {
  if (b == 0) {
    throw std::invalid_argument("Input Error: can't divide by zero!");
  }
  return static_cast<float>(a) / b;
}
