#include "readFreq.h"

#include <stdio.h>

//#include <cstdio>
#include <cstdlib>
#include <fstream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  std::ifstream fr(fname);
  if (fr.fail()) {
    std::cerr << "file open failed" << std::endl;
    exit(EXIT_FAILURE);
  }
  int ch;
  uint64_t * cnt;
  cnt = new uint64_t[257]();
  while ((ch = fr.get()) != EOF) {
    cnt[ch]++;
  }
  cnt[256]++;
  fr.close();
  return cnt;
  //WRITE ME!
}
