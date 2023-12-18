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
    Story s;
    s.addir(std::string(argv[1]));
    std::ifstream f(getStoryName(argv[1]).c_str());
    std::string line;
    while (!f.eof()) {
      std::getline(f, line);
      if (line.empty()) {
        continue;
      }
      else if (isPageDec(line)) {
        s.addPFromPath(line);
      }
      else {
        s.addChoiceFromPath(line);
      }
    }
    s.printStory();
  }
  catch (std::exception & e) {
    putError(e.what());
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
