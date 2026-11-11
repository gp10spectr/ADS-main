// Copyright 2026 Khaferl Pavel

#include "lib_vector/tmemdata.h"

int calculate_capacity(int required) {
  if (required <= 0) {
    return 0;
  }
  return ((required + MEM_STEP - 1) / MEM_STEP) * MEM_STEP;
}
