#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 4 && argc != 3) {
    putError("invalid argc.");
  }

  if (argc == 4) {
    if (strcmp(argv[1], "-n") != 0) {
      putError("invalid option.");
    }
    catarray_t * cats = getCats(argv[2]);
    story * s = readLines(argv[3]);
    category_t preWords;
    preWords.n_words = 0;
    preWords.name = "preWords";
    preWords.words = NULL;

    putWords(s, cats, &preWords, 1);
    for (size_t i = 0; i < s->lineSize; i++) {
      printf("%s", s->lines[i]);
    }

    //    for (size_t i = 0; i < cats->n; i++) {
    //for (size_t j = 0; j < cats->arr[i].n_words; j++) {
    //  free(cats->arr[i].words[j]);
    //}
    //free(cats->arr[i].name);
    //free(cats->arr[i].words);
    //}
    //free(cats->arr);
    //free(cats);

    freeCats(cats);

    //for (size_t i = 0; i < s->lineSize; i++) {
    //free(s->lines[i]);
    //}
    //free(s->lines);
    //free(s);

    freeStory(s);

    //for (size_t i = 0; i < preWords.n_words; i++) {
    //free(preWords.words[i]);
    //}
    //free(preWords.words);
    freeCate(&preWords);

    return EXIT_SUCCESS;
  }

  if (argc == 3) {
    catarray_t * cats = getCats(argv[1]);
    story * s = readLines(argv[2]);
    category_t preWords;
    preWords.n_words = 0;
    preWords.name = "preWords";
    preWords.words = NULL;

    putWords(s, cats, &preWords, 0);
    for (size_t i = 0; i < s->lineSize; i++) {
      printf("%s", s->lines[i]);
    }

    //for (size_t i = 0; i < cats->n; i++) {
    //for (size_t j = 0; j < cats->arr[i].n_words; j++) {
    //  free(cats->arr[i].words[j]);
    //}
    //free(cats->arr[i].name);
    //free(cats->arr[i].words);
    //}
    //free(cats->arr);
    //free(cats);

    freeCats(cats);

    //for (size_t i = 0; i < s->lineSize; i++) {
    //free(s->lines[i]);
    //}
    //free(s->lines);
    //free(s);

    freeStory(s);

    //for (size_t i = 0; i < preWords.n_words; i++) {
    //free(preWords.words[i]);
    //}
    //free(preWords.words);

    freeCate(&preWords);

    return EXIT_SUCCESS;
  }

  //return EXIT_SUCCESS;
}
