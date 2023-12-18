#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "Page.hpp"
#include "errorHandle.h"
#include "helperfunc.h"

int main(int argc, char ** argv) {
  try {
    if (argc != 2) {
      throw errArg();
    }
  }
  catch (std::exception & e) {
    putError(e.what());
    return EXIT_FAILURE;
  }
  try {
    Story s = Story(std::string(argv[1]));
    if (!s.vldStory()) {
      throw errVLD();
    }
    std::set<size_t> v;
    s.dfsRec(0, "", v);
    if (s.getdfsRes().empty()) {
      std::cout << "This story is unwinnable!" << std::endl;
    }
    else {
      for (size_t i = 0; i < s.getdfsRes().size(); i++) {
        std::cout << s.getdfsRes()[i] << std::endl;
      }
    }
  }
  catch (std::exception & e) {
    putError(e.what());
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
