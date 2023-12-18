#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char ** argv) {
  if (argc == 1) {
    std::string strval;
    std::vector<std::string> strList;
    while (!std::cin.eof()) {
      std::getline(std::cin, strval);
      strList.push_back(strval);
    }
    std::sort(strList.begin(), strList.end());
    std::vector<std::string>::iterator itr = strList.begin();
    while (itr != strList.end()) {
      std::cout << *itr << std::endl;
      itr++;
    }
    strList.clear();
  }
  else {
    for (int i = 2; i < argc; i++) {
      std::ifstream readFile(argv[i]);
      if (readFile.fail()) {
        std::cerr << "fail open" << argv[i] << std::endl;
        exit(EXIT_FAILURE);
      }
      std::string strval;
      std::vector<std::string> strList;
      while (!readFile.eof()) {
        std::getline(readFile, strval);
        strList.push_back(strval);
      }

      std::sort(strList.begin(), strList.end());
      std::vector<std::string>::iterator itr = strList.begin();
      while (itr != strList.end()) {
        std::cout << *itr << std::endl;
        itr++;
      }
      strList.clear();
    }
  }
  return EXIT_SUCCESS;
}
