#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  counts_t * count = malloc(sizeof(*count));
  if (count == NULL) {
    fprintf(stderr, "No enough memory");
    exit(EXIT_FAILURE);
  }
  count->cntArray = NULL;
  count->cntLength = 0;
  count->unknownName = 0;

  return count;
  //WRITE ME
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (c == NULL) {
    fprintf(stderr, "invalid count");
    exit(EXIT_FAILURE);
  }
  if (name == NULL) {
    c->unknownName++;
    return;
  }
  for (size_t i = 0; i < c->cntLength; i++) {
    if (strcmp(name, c->cntArray[i].str) == 0) {
      c->cntArray[i].cnt++;
      return;
    }
  }
  c->cntLength++;
  c->cntArray = realloc(c->cntArray, c->cntLength * sizeof(*c->cntArray));
  one_count_t temp;
  temp.cnt = 1;
  temp.str = strdup(name);
  c->cntArray[c->cntLength - 1] = temp;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i = 0; i < c->cntLength; i++) {
    fprintf(outFile, "%s: %d\n", c->cntArray[i].str, c->cntArray[i].cnt);
  }
  if (c->unknownName != 0) {
    fprintf(outFile, "<unknown> : %d\n", c->unknownName);
  }
}

void freeCounts(counts_t * c) {
  for (size_t i = 0; i < c->cntLength; i++) {
    free(c->cntArray[i].str);
  }
  free(c->cntArray);
  free(c);
  //WRITE ME
}
