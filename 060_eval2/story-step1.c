#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    putError("invalid argc");
  }

  story * s = readLines(argv[1]);

  putWords(s, NULL, NULL, 0);

  for (size_t i = 0; i < s->lineSize; i++) {
    printf("%s", s->lines[i]);
  }

  //  for (size_t i = 0; i < s->lineSize; i++) {
  //free(s->lines[i]);
  //}
  //free(s->lines);
  //free(s);

  freeStory(s);
  return EXIT_SUCCESS;
}
