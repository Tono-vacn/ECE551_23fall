#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

int powerTest(unsigned x, unsigned y, unsigned res) {
  unsigned result = power(x, y);
  if (result != res) {
    exit(EXIT_FAILURE);
  };
  return 0;
};

int main() {
  powerTest(0, 0, 1);
  powerTest(2, 2, 4);
  powerTest(1, 1, 1);
  powerTest(2, 6, 64);
  powerTest(3, 3, 27);
  powerTest(0, 1, 0);
  powerTest(65537, 1, 65537);
  return EXIT_SUCCESS;
}
