#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

void putError(char * message) {
  fprintf(stderr, "%s", message);
  exit(EXIT_FAILURE);
}

void failError() {
  perror("Failed");
  exit(EXIT_FAILURE);
}

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    failError();
  }
  char * rl = NULL;
  size_t length = 0;
  counts_t * c = createCounts();
  while (getline(&rl, &length, f) > 0) {
    char * ed = strchr(rl, '\n');
    if (ed != NULL)
      *ed = '\0';
    addCount(c, lookupValue(kvPairs, rl));
    free(rl);
    rl = NULL;
  }
  free(rl);
  //int res = fclose(f);
  if (fclose(f) != 0) {
    failError();
  }

  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc <= 2) {
    putError("lacks arg");
  }
  kvarray_t * keyVal = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * cnt = countFile(argv[i], keyVal);
    //compute the output file name from argv[i] (call this outName)
    char * outputName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outputName, "w");
    if (f == NULL) {
      failError();
    }
    //print the counts from c into the FILE f
    printCounts(cnt, f);
    //close f
    if (fclose(f) != 0) {
      failError();
    }
    //free the memory for outName and c
    //free(keyVal);
    //freeKVs(keyVal);
    freeCounts(cnt);
    free(outputName);
  }
  //free the memory for kv
  freeKVs(keyVal);
  return EXIT_SUCCESS;
}
