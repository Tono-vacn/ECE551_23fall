#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("open file failed");
    exit(EXIT_FAILURE);
  }
  kvarray_t * res = malloc(sizeof(*res));
  if (res == NULL) {
    perror("not enough mem");
    exit(EXIT_FAILURE);
  }
  res->pairs = malloc(sizeof(*res->pairs));
  if (res->pairs == NULL) {
    perror("not enough mem");
    exit(EXIT_FAILURE);
  }
  res->length = 0;
  char * tempStr = NULL;
  size_t tempLeng = 0;
  while (getline(&tempStr, &tempLeng, f) > 0) {
    res->pairs = realloc(res->pairs, (res->length + 1) * sizeof(*res->pairs));

    char * eq = strchr(tempStr, '=');
    if (eq == NULL) {
      perror("can not get = ");
      exit(EXIT_FAILURE);
    }

    //kvpair_t * tempkv = malloc(sizeof(*tempkv));
    //tempkv->key = tempStr;

    //res->pairs[res->length].key = tempStr;

    //size_t keyLength = eq-tempStr;
    //res->pairs[res->length]

    *eq = '\0';
    res->pairs[res->length].key = strdup(tempStr);
    //tempkv->value = eq + 1;

    //res->pairs[res->length].value = eq + 1;

    char * ed = strchr(eq + 1, '\n');

    if (ed != NULL) {
      *ed = '\0';
    }
    res->pairs[res->length].value = strdup(eq + 1);
    //res->pairs[res->length] = *tempkv;
    res->length++;
    free(tempStr);
    tempStr = NULL;
  }
  //WRITE ME
  int resf = fclose(f);
  if (resf != 0) {
    perror("fail to close file");
    exit(EXIT_FAILURE);
  }
  free(tempStr);
  return res;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->length; i++) {
    if (pairs->pairs[i].key != NULL) {
      free(pairs->pairs[i].key);
    }
    if (pairs->pairs[i].value != NULL) {
      free(pairs->pairs[i].value);
    }
  }
  free(pairs->pairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->length; i++) {
    printf("key = '%s' value = '%s'\n", pairs->pairs[i].key, pairs->pairs[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->length; i++) {
    if (strcmp(pairs->pairs[i].key, key) == 0) {
      return pairs->pairs[i].value;
    }
  }
  return NULL;
}
