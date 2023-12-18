#include <cmath>
#include <cstdlib>
#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  while (low < high - 1) {
    int mid = (high + low) / 2;
    int res = f->invoke(mid);
    if (res == 0) {
      return mid;
    }
    else if (res > 0) {
      high = mid;
    }
    else {
      low = mid;
    }
  }
  return low;
}
