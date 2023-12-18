#ifndef __COUNTS_H__
#define __COUNTS_H__
#include <stdio.h>
struct _one_count_t {
  //DEFINE ME
  int cnt;
  char * str;
};
typedef struct _one_count_t one_count_t;

struct _counts_t {
  //DEFINE ME
  size_t cntLength;
  one_count_t * cntArray;
  int unknownName;
};
typedef struct _counts_t counts_t;

counts_t * createCounts(void);
void addCount(counts_t * c, const char * name);
void printCounts(counts_t * c, FILE * outFile);

void freeCounts(counts_t * c);

#endif
