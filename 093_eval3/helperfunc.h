#ifndef HELPERFUNC_H__
#define HELPERFUNC_H__

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

//#include "Page.hpp"
#include "errorHandle.h"

void checkRefArray(std::vector<int> & refRec) {
  for (size_t i = 1; i < refRec.size(); i++) {
    if (refRec[i] == -1 || refRec[i] != 0) {
      //std::cout << refRec[i] << " " << i << std::endl;
      throw errRef();
    }
  }
}

void recRefArrayV(std::vector<std::pair<std::pair<size_t, std::string>,
                                        std::pair<std::string, long int> > > & pgc,
                  std::vector<int> & refRec,
                  size_t maxPage) {
  for (size_t i = 0; i < pgc.size(); i++) {
    if (pgc[i].first.first < 0 || pgc[i].first.first > maxPage) {
      throw errOutRange();
    }
    refRec[pgc[i].first.first] = 0;
  }
}

void recRefArray(std::vector<std::pair<size_t, std::string> > & pgc,
                 std::vector<int> & refRec,
                 size_t maxPage) {
  for (std::vector<std::pair<size_t, std::string> >::iterator itr = pgc.begin();
       itr != pgc.end();
       ++itr) {
    if (itr->first < 0 || itr->first > maxPage) {
      throw errOutRange();
    }
    refRec[itr->first] = 0;
  }
}

bool cinCheck() {
  if (std::cin.fail()) {
    throw errWIpt();
  }
  if (std::cin.eof()) {
    throw errWIpt();
  }
  return true;
}

bool isNum(const std::string & s) {
  if (s.size() == 0) {
    return false;
  }
  else {
    for (size_t i = 0; i < s.size(); i++) {
      if (s[i] < '0' || s[i] > '9') {
        return false;
      }
    }
  }
  return true;
}

bool isPageDec(std::string & line) {
  size_t pos = line.find('@');
  if (pos == std::string::npos) {
    return false;
  }
  else {
    return true;
  }
}

bool isVarDec(std::string & line) {
  size_t pos = line.find('$');
  if (pos == std::string::npos) {
    return false;
  }
  else {
    return true;
  }
}

bool isVarChoice(std::string & line) {
  size_t posl = line.find('[');
  size_t posr = line.find(']');
  if (posl == std::string::npos || posr == std::string::npos) {
    return false;
  }
  else if (posr <= posl) {
    throw errSLine();
  }
  else {
    return true;
  }
}

bool isNomChoice(std::string & line) {
  size_t posl = line.find(':');
  size_t posr = line.find(':', posl + 1);
  if (posl == std::string::npos || posr == std::string::npos) {
    throw errSLine();
  }
  else {
    return true;
  }
}

//Story & getStory(Story & s, std::string & dir) {
//s.addir(dir);
//std::ifstream f(std::string(dir + "/story.txt").c_str());
//std::string line;
//while (!f.eof()) {
//  std::getline(f, line);
//  if (line.empty()) {
//    continue;
//  }
//  else if (isPageDec(line)) {
//    s.addPFromPath(line);
//  }
//  else {
//    s.addChoiceFromPath(line);
//  }
//}
//return s;
//}

std::string getStoryName(const char * c) {
  std::string str(c);
  std::string fullname = str + "/story.txt";
  return fullname;
}

int sToNum(std::string & tar) {
  std::istringstream toN(tar);
  int res;
  if (!(toN >> res)) {
    throw errNumConv();
  }
  return res;
}

//bool isPageDec(std::string & line) {
//size_t pos = line.find('@');
//if (pos == std::string::npos) {
//  return false;
//}
//else {
//  return true;
//}
//}

#endif
