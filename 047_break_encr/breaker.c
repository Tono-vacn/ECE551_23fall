#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void breaken(FILE * f) {
  int ch;
  int freq[26];
  int maxf = 0;
  int maxi = 0;
  for (int i = 0; i < 26; i++) {
    freq[i] = 0;
  }
  while ((ch = fgetc(f)) != EOF) {
    if (isalpha(ch)) {
      ch = tolower(ch);
      ch -= 'a';
      freq[ch]++;
      //maxf = maxf < freq[ch] ? freq[ch] : maxf;
      //maxi = maxf < freq[ch] ? ch : maxi;
    }
  }
  for (int i = 0; i < 26; i++) {
    if (freq[i] > maxf) {
      maxf = freq[i];
      maxi = i;
    }
  }
  if (maxf == 0) {
    fprintf(stderr, "No letters\n");
    exit(EXIT_FAILURE);
  }
  int en = maxi - 4 >= 0 ? maxi - 4 : maxi + 22;
  fprintf(stdout, "%d\n", en);
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: breaker inpurFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  breaken(f);
  if (fclose(f) != 0) {
    perror("Failed to close the file");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
