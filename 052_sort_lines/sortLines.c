#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void putErr(char * message) {
  perror(message);
  exit(EXIT_FAILURE);
}

void sortStr(FILE * f) {
  char ** ls = malloc(sizeof(*ls));
  if (ls == NULL) {
    //perror("need more mem");
    //exit(EXIT_FAILURE);
    putErr("need more memory");
  }
  char * l = NULL;
  size_t lc = 0;
  size_t cc = 0;
  while (getline(&l, &cc, f) >= 0) {
    char ** temp = realloc(ls, (lc + 1) * (sizeof(*ls)));
    if (temp == NULL) {
      putErr("need more memory");
    }
    ls = temp;
    ls[lc] = l;
    lc++;
    l = NULL;
  }

  sortData(ls, lc);
  for (size_t i = 0; i < lc; i++) {
    printf("%s", ls[i]);
    free(ls[i]);
  }
  free(ls);
  free(l);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    FILE * f = stdin;
    if (f == NULL) {
      //perror("open file failed");
      //return EXIT_FAILURE;
      putErr("open file failed");
    }
    sortStr(f);
    //if (fclose(f) != 0) {
    //perror("close file failed");
    //return EXIT_FAILURE;
    //putErr("close Failure");
    //}
    //free(f);
  }

  if (argc > 1) {
    for (size_t i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        putErr("open failed");
        //perror("open file failed");
        //return EXIT_FAILURE;
      }
      sortStr(f);
      if (fclose(f) != 0) {
        putErr("close failed");
        //perror("close failed");
        //return EXIT_FAILURE;
      }
    }
  }

  return EXIT_SUCCESS;
}
