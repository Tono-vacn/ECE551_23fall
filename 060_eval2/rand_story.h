#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
//any functions you want your main to use

struct story_t {
  char ** lines;
  size_t lineSize;
};

typedef struct story_t story;

void putError(const char * message);

story * readLines(const char * fileName);

void putWords(story * s, catarray_t * cats, category_t * preWords, int dup);

char * modifyLines(char * line, catarray_t * cats, category_t * preWords, int dup);

const char * getRandomWord(char * blank,
                           catarray_t * cats,
                           category_t * preWords,
                           int dup);

void deepCopyCat(category_t * temp, category_t src);

catarray_t * getCats(char * fileName);

void removeWords(catarray_t * cats, size_t index, char * word);

void freeStory(story * s);

void freeCats(catarray_t * cats);

void freeCate(category_t * cate);

void freeCatsArr(catarray_t * cats);
#endif
