#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>

#include "node.h"
#include "readFreq.h"

void writeHeader(BitFileWriter * bfw, const std::map<unsigned, BitString> & theMap) {
  for (int i = 0; i < 257; i++) {
    std::map<unsigned, BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size());
      bfw->writeBitString(it->second);
    }
    else {
      bfw->writeByte(0);
    }
  }
}

void writeCompressedOutput(const char * inFile,
                           const char * outFile,
                           const std::map<unsigned, BitString> & theMap) {
  BitFileWriter bfw(outFile);
  writeHeader(&bfw, theMap);

  //WRITE YOUR CODE HERE!
  //open the input file for reading

  std::ifstream fr(inFile);

  //You need to read the input file, lookup the characters in the map,
  //and write the proper bit string with the BitFileWriter

  if (fr.fail()) {
    std::cerr << "file open failed" << std::endl;
    exit(EXIT_FAILURE);
  }

  int c;
  //char ch;
  while ((c = fr.get()) != EOF) {
    std::map<unsigned, BitString>::const_iterator itr = theMap.find(c);
    if (itr == theMap.end()) {
      std::cerr << "no correct character" << std::endl;
      exit(EXIT_FAILURE);
    }
    bfw.writeBitString(itr->second);
  }

  std::map<unsigned, BitString>::const_iterator itend = theMap.find(256);
  //dont forget to lookup 256 for the EOF marker, and write it out.
  bfw.writeBitString(itend->second);
  //BitFileWriter will close the output file in its destructor
  //but you probably need to close your input file.
  fr.close();
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: compress input output\n");
    return EXIT_FAILURE;
  }
  //WRITE YOUR CODE HERE
  //Implement main
  //hint 1: most of the work is already done.
  //hint 2: you can look at the main from the previous tester for 90% of this

  uint64_t * f = readFrequencies(argv[1]);

  Node * tr = buildTree(f);

  std::map<unsigned, BitString> mp;

  BitString bt;

  tr->buildMap(bt, mp);

  writeCompressedOutput(argv[1], argv[2], mp);

  delete[] f;

  delete tr;

  return EXIT_SUCCESS;
}
