#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  size_t cnt = 1;
  size_t res = 0;
  if (array == NULL || n <= 1) {
    return n == 0 ? 0 : 1;
  }
  for (size_t i = 1; i < n; i++) {
    if (array[i] > array[i - 1]) {
      cnt++;
    }
    else {
      cnt = 1;
    }
    res = res > cnt ? res : cnt;
  }
  return res;
}
