#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    putError("wrong number for argc.");
  }

  catarray_t * cats = getCats(argv[1]);
  printWords(cats);

  //  for (size_t i = 0; i < cats->n; i++) {
  //for (size_t j = 0; j < cats->arr[i].n_words; j++) {
  //  free(cats->arr[i].words[j]);
  //}
  //free(cats->arr[i].name);
  //free(cats->arr[i].words);
  //}
  //free(cats->arr);
  //free(cats);

  freeCats(cats);
  return EXIT_SUCCESS;
}
