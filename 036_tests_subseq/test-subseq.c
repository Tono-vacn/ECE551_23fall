#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n);

int testMaxSeq(int * inputarray, size_t n, size_t outputSize) {
  size_t result = maxSeq(inputarray, n);
  if (result != outputSize) {
    exit(EXIT_FAILURE);
  }
  return 0;
}

int main() {
  int array_1[] = {1, 1, 1, 1, 1, 1, 2, 1};
  int array_2[] = {1, 2, 3, 4, -5, -4, -3, -2, -1};
  int array_3[] = {-100, -99, -98, -97, -96};
  size_t l1 = 3;
  size_t r1 = 1;
  size_t l2 = 5;
  size_t r2 = 4;
  testMaxSeq(array_1, l1, r1);
  l1 = 7;
  r1 = 2;
  testMaxSeq(array_1, l1, r1);
  testMaxSeq(array_2, l2, r2);
  l2 = 9;
  r2 = 5;
  testMaxSeq(array_2, l2, r2);
  testMaxSeq(array_3, 5, 5);
  testMaxSeq(&array_3[1], 4, 4);
  testMaxSeq(NULL, 0, 0);

  printf("all done");
  return EXIT_SUCCESS;
}
