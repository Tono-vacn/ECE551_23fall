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
    Story s = Story(std::string(argv[1]));
    if (!s.vldStory()) {
      throw errVLD();
    };
    s.userReadStory();
  }
  catch (std::exception & e) {
    putError(e.what());
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
