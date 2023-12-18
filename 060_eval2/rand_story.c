#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>

void putError(const char * message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}

story * readLines(const char * fileName) {
  FILE * f = fopen(fileName, "r");
  if (f == NULL) {
    putError("can't open file.");
  }
  char * line = NULL;
  size_t size = 0;
  story * s = malloc(sizeof(*s));
  s->lines = NULL;
  s->lineSize = 0;
  while (getline(&line, &size, f) >= 0) {
    s->lines = realloc(s->lines, (s->lineSize + 1) * sizeof(*s->lines));
    s->lines[s->lineSize] = strdup(line);
    s->lineSize++;
    free(line);
    line = NULL;
  }
  free(line);
  if (fclose(f) != 0) {
    putError("can't close file.");
  }
  return s;
}

char * modifyLines(char * line, catarray_t * cats, category_t * preWords, int dup) {
  /*this function will modify lines from story template*/
  //  size_t lineSz = strlen(line);
  char * res = malloc(sizeof(*res));
  while (strchr(line, '_') != NULL) {
    size_t lineSz = strlen(line);
    char * posl = strchr(line, '_');
    if (posl == NULL) {
      break;
    }
    char * posr = strchr(posl + 1, '_');
    if (posr == NULL) {
      putError("_ don't pair.");
    }
    char * blank = strndup(posl + 1, posr - posl - 1);
    //const char * newWord = chooseWord(blank, cats);

    const char * newWord = getRandomWord(blank, cats, preWords, dup);

    free(blank);
    size_t newWordSz = strlen(newWord);
    //size_t lineSz = strlen(line);
    size_t resSz = lineSz - (posr - posl + 1) + newWordSz;
    //char * res = malloc((resSz + 1) * sizeof(*res));
    res = realloc(res, (resSz + 1) * sizeof(*res));
    res[resSz] = '\0';
    size_t leftSz = posl - line;

    //get the old data from line

    for (size_t i = 0; i < leftSz; i++) {
      res[i] = line[i];
    }

    //put the new words
    for (size_t i = leftSz; i < leftSz + newWordSz; i++) {
      res[i] = newWord[i - leftSz];
    }

    //put the rest of the old line
    for (size_t i = leftSz + newWordSz; i < resSz; i++) {
      res[i] = line[i - newWordSz + posr - posl + 1];
    }

    free(line);
    line = strdup(res);
  }
  free(res);
  return line;
}

const char * getRandomWord(char * blank,
                           catarray_t * cats,
                           category_t * preWords,
                           int dup) {
  /*this function would choose the right words for every blank, and the variable dup indicates the mode whether remove used words*/

  //put 'cats' if category is NULL as ordered
  if (cats == NULL) {
    return chooseWord(blank, NULL);
  }

  //put error if no words remain
  if (cats->n == 0 || cats->arr == NULL) {
    putError("all words are removed.");
  }
  for (size_t i = 0; i < cats->n; i++) {
    if (strcmp(blank, cats->arr[i].name) == 0) {
      if (cats->arr[i].n_words == 0 || cats->arr[i].words == NULL) {
        putError("words for certain category have ran out.");
      }

      const char * res = chooseWord(blank, cats);

      //preWords should always be initialized outside
      if (preWords == NULL) {
        putError("invalid previous words.");
      }

      if (preWords != NULL) {
        preWords->n_words += 1;
        preWords->words =
            realloc(preWords->words, preWords->n_words * sizeof(*preWords->words));
        preWords->words[preWords->n_words - 1] = strdup(res);
      }

      //use removeWords to delete used words
      if (dup == 1) {
        removeWords(cats, i, preWords->words[preWords->n_words - 1]);
      }
      //if(preWords==NULL){}
      //here can't return res since it is not deep copied
      return preWords->words[preWords->n_words - 1];
    }
  }

  //logic for get history words
  if (atoi(blank) > 0) {
    if (preWords != NULL) {
      int idx = preWords->n_words - atoi(blank);
      if (idx < 0) {
        putError("index out of range");
      }
      const char * res = preWords->words[idx];
      preWords->n_words++;
      preWords->words =
          realloc(preWords->words, preWords->n_words * sizeof(*preWords->words));
      preWords->words[preWords->n_words - 1] = strdup(res);
      return res;
    }
    putError("invalid input index");
  }

  putError("blanks contain invalid prompts");
  return NULL;
}

//return blank;
//}

void removeWords(catarray_t * cats, size_t index, char * word) {
  /*remove used words from cats*/
  cats->arr[index].n_words--;
  if (cats->arr[index].n_words == 0) {
    cats->n -= 1;
    //the whole catarray is empty
    if (cats->n == 0) {
      cats->n++;
      cats->arr[index].n_words++;
      freeCatsArr(cats);
      cats->n--;
      //make sure that this ptr won't be free twice
      cats->arr = NULL;
    }
    else {
      //only the category is empty
      //deep copy the whole cats
      category_t * temp = malloc((cats->n) * sizeof(*temp));
      size_t cnt = 0;
      for (size_t i = 0; i < cats->n + 1; i++) {
        if (i != index) {
          deepCopyCat(temp + cnt, cats->arr[i]);
          cnt++;
        }
        else {
          continue;
        }
      }
      cats->n++;
      cats->arr[index].n_words++;
      freeCatsArr(cats);
      cats->n--;
      cats->arr = temp;
    }
  }
  else {
    //only remove one word
    char ** newList = malloc((cats->arr[index].n_words) * sizeof(*newList));
    size_t listCnt = 0;
    for (size_t i = 0; i < cats->arr[index].n_words + 1; i++) {
      if (strcmp(word, cats->arr[index].words[i]) != 0) {
        newList[listCnt] = strdup(cats->arr[index].words[i]);
        listCnt++;
      }
      free(cats->arr[index].words[i]);
    }
    free(cats->arr[index].words);
    cats->arr[index].words = newList;
    //cats->arr[index].n_words--;
  }
}

void deepCopyCat(category_t * temp, category_t src) {
  /*this function will deepcopy a category_t from source*/
  temp->name = strdup(src.name);
  temp->n_words = src.n_words;
  temp->words = malloc(temp->n_words * sizeof(*temp->words));
  for (size_t i = 0; i < src.n_words; i++) {
    temp->words[i] = strdup(src.words[i]);
  }
}

void putWords(story * s, catarray_t * cats, category_t * preWords, int dup) {
  /* this function whill modify the whole story line by line*/
  for (size_t i = 0; i < s->lineSize; i++) {
    s->lines[i] = modifyLines(s->lines[i], cats, preWords, dup);
  }
}

catarray_t * getCats(char * fileName) {
  FILE * f = fopen(fileName, "r");
  if (f == NULL) {
    putError("invalid cat file.");
  }
  char * line = NULL;
  size_t size = 0;
  catarray_t * cats = malloc(sizeof(*cats));
  cats->n = 0;
  cats->arr = NULL;
  while (getline(&line, &size, f) >= 0) {
    char * col = strchr(line, ':');
    char * ed = strchr(line, '\n');

    if (col == NULL || ed == NULL) {
      putError("invalid format for catagory.");
    }

    size_t catSize = col - line;
    size_t nameSize = ed - col - 1;

    char * cat = strndup(line, catSize);
    char * nameVal = strndup(col + 1, nameSize);
    int flag = 0;
    for (size_t i = 0; i < cats->n; i++) {
      if (strcmp(cat, cats->arr[i].name) == 0) {
        //exsisting cate
        cats->arr[i].words = realloc(
            cats->arr[i].words, (cats->arr[i].n_words + 1) * sizeof(*cats->arr[i].words));
        cats->arr[i].words[cats->arr[i].n_words] = nameVal;
        cats->arr[i].n_words += 1;
        flag = 1;
        free(cat);
        break;
      }
    }
    if (flag == 0) {
      //new cate
      cats->n++;
      cats->arr = realloc(cats->arr, cats->n * sizeof(*cats->arr));
      category_t newcat;
      newcat.name = cat;
      newcat.n_words = 1;
      newcat.words = malloc(sizeof(*newcat.words));
      newcat.words[0] = nameVal;
      cats->arr[cats->n - 1] = newcat;
    }

    free(line);
    line = NULL;
  }
  free(line);
  if (fclose(f) != 0) {
    putError("can't close file.");
  }
  return cats;
}

void freeStory(story * s) {
  /*this function frees story struct*/
  for (size_t i = 0; i < s->lineSize; i++) {
    free(s->lines[i]);
  }
  free(s->lines);
  free(s);
}

void freeCats(catarray_t * cats) {
  /*this function frees the whole part of catarray_t struct*/
  for (size_t i = 0; i < cats->n; i++) {
    for (size_t j = 0; j < cats->arr[i].n_words; j++) {
      free(cats->arr[i].words[j]);
    }
    free(cats->arr[i].name);
    free(cats->arr[i].words);
  }
  free(cats->arr);
  free(cats);
}

void freeCatsArr(catarray_t * cats) {
  /*this function will free the category array of catarray_t*/
  for (size_t i = 0; i < cats->n; i++) {
    for (size_t j = 0; j < cats->arr[i].n_words; j++) {
      free(cats->arr[i].words[j]);
    }
    free(cats->arr[i].name);
    free(cats->arr[i].words);
  }
  free(cats->arr);
}

void freeCate(category_t * cate) {
  /*this function will free the category
_t struct*/
  for (size_t i = 0; i < cate->n_words; i++) {
    free(cate->words[i]);
  }
  free(cate->words);
}
