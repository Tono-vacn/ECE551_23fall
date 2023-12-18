#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  const char * tail = ".counts";
  size_t len = strlen(inputName) + strlen(tail) + 1;
  char * outputName = malloc(len * sizeof(*outputName));
  snprintf(outputName, len, "%s%s", inputName, tail);
  return outputName;
}
