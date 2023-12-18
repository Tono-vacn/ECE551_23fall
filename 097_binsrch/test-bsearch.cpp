#include <cmath>
#include <cstdio>
#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int count;
  if (high > low) {
    count = log(high - low) / log(2) + 1;
  }
  else {
    count = 1;
  }
  CountedIntFn * func = new CountedIntFn(count, f, mesg);
  int res = binarySearchForZero(func, low, high);
  if (res != expected_ans) {
    fprintf(stderr, "wrong res: %s", mesg);
    exit(EXIT_FAILURE);
  }
}

class negF : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return -1; }
};

class posF : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 1; }
};

class posLinearF : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 3 * arg + 3; }
};

class negLinearF : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return -2 * arg; }
};

class sinF : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

int main() {
  sinF sinf;
  negLinearF nlf;
  posLinearF plf;
  posF pf;
  negF nf;

  check(&sinf, 0, 150000, 52359, "Sin");

  check(&nf, -100, 100, 99, "neg (-100,100)");
  //1-5
  check(&nf, 10, 1500, 1499, "neg (1,1500)");
  check(&nf, -100, -10, -11, "neg (-100,-10)");
  check(&nf, 0, 0, 0, "neg (0,0)");
  //None
  check(&pf, -100, 150, -100, "pos (-100,150)");
  check(&pf, -100, -10, -100, "pos (-100,-10)");
  check(&pf, 10, 100, 10, "pos (10,100)");
  check(&pf, 0, 0, 0, "pos (0,0)");
  //None
  check(&plf, -100, 100, -1, "plf (-100,100)");
  check(&plf, -100, -20, -21, "plf (-100,-20)");
  check(&plf, 10, 200, 10, "plf (10,200)");
  check(&plf, 0, 0, 0, "plf (0,0)");
}
