#include <cstdlib>
#include <iostream>
#include <string>

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
    Story s = Story(std::string(argv[1]), 0);

    //    std::cout << s.getVarget().size() << std::endl;

    //Page test = s.getPageByNum(5);

    //std::cout << test.getVarChoice().size() << std::endl;
    //std::cout << test.getVar().size() << std::endl;

    if (!s.vldStoryWithVar()) {
      throw errVLD();
    }
    s.userReadStoryWithVar();
  }
  catch (std::exception & e) {
    putError(e.what());
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
