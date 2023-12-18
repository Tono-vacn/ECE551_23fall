#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
void puterror(const char * er) {
  fprintf(stderr, "%s", er);
  exit(EXIT_FAILURE);
}

void rotate(FILE * f) {
  char outMatrtix[10][10] = {"0000000000",
                             "0000000000",
                             "0000000000",
                             "0000000000",
                             "0000000000",
                             "0000000000",
                             "0000000000",
                             "0000000000",
                             "0000000000",
                             "0000000000"};
  char line[12] = "000000000000";  //12
  int countline = 0;
  //int charc;
  for (countline = 0; countline < 10; countline++) {  //12
    if (fgets(line, 12, f) != NULL) {
      //countline++;
      //why choose 12: fgets will atomatically add an '\0' to the end of the stream
      if (line[10] != '\n'
          //|| line[11] != '\0'
      ) {
        puterror("line out of boundry");
      }
      for (int i = 10; i > 0; i--) {
        outMatrtix[10 - i][9 - countline] = line[10 - i];
      }
    }
    else {
      puterror("need more lines");
    }
  }

  if (fgets(line, 12, f) != NULL) {
    puterror("too many lines");
  }

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      fprintf(stdout, "%c", outMatrtix[i][j]);
    }
    fprintf(stdout, "\n");
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix inputFIleName");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }
  rotate(f);
  if (fclose(f) != 0) {
    perror("can't close the file");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
