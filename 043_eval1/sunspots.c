#include "sunspots.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
ss_monthly_t parseLine(char * line) {
  // WRITE ME
  /* This function parse the input string line and format them to standard timestamp*/
  ss_monthly_t ans;
  ans.year = 0;
  ans.month = 0;
  ans.num = 0;

  char * posComma = strchr(line, ',');
  if (posComma == NULL) {
    fprintf(stderr, "no comma in line");
    exit(EXIT_FAILURE);
  }
  char * posDash = strchr(line, '-');
  if (posDash == NULL) {
    fprintf(stderr, "no dash in line");
    exit(EXIT_FAILURE);
  }

  //*posComma = '\0';
  char * endptr;
  ans.year = strtol(line, &endptr, 10);
  if (*endptr != '-') {
    fprintf(stderr, "wrong format for year");
    exit(EXIT_FAILURE);
  }
  if (ans.year > 9999 || ans.year < 0) {
    fprintf(stderr, "wrong value for year");
    exit(EXIT_FAILURE);
  }
  endptr = NULL;
  ans.month = strtol(posDash + 1, &endptr, 10);
  if (*endptr != ',') {
    fprintf(stderr, "wrong format for month");
    exit(EXIT_FAILURE);
  }
  if (ans.month > 12 || ans.month < 1) {
    fprintf(stderr, "wrong value for month");
    exit(EXIT_FAILURE);
  }
  endptr = NULL;
  ans.num = strtod(posComma + 1, &endptr);
  if (*endptr != '\n') {
    fprintf(stderr, "wrong format for number");
    exit(EXIT_FAILURE);
  }
  //if()
  return ans;
}

void meanFilter(ss_monthly_t * data, size_t n, ss_monthly_t * mean, unsigned w) {
  // WRITE ME
  /* This function deployed meanfilter to the input time series based on a sliding window*/
  if (data == NULL) {
    fprintf(stderr, "data not valid");
    exit(EXIT_FAILURE);
  }
  if (mean == NULL) {
    fprintf(stderr, "mean not valid");
    exit(EXIT_FAILURE);
  }
  if (w > n) {
    fprintf(stderr, "w should not be larger than n");
    exit(EXIT_FAILURE);
  }
  if (w % 2 == 0) {
    fprintf(stderr, "w should be odd int");
    exit(EXIT_FAILURE);
  }
  if (n <= 0) {
    fprintf(stderr, "invalid length");
    exit(EXIT_FAILURE);
  }
  size_t l = 0;
  size_t r = w / 2;
  double sumVal = 0;
  for (size_t i = l; i <= r; i++) {
    sumVal += data[i].num;
  }
  for (size_t i = 0; i < n; i++) {
    if (r < w - 1) {
      mean[i].num = sumVal / (r - l + 1);
      mean[i].month = data[i].month;
      mean[i].year = data[i].year;
      r++;
      sumVal += data[r].num;
    }
    //else if (r == n - 1) {
    //mean[i].num = sumVal / (r - l + 1);
    //mean[i].month = data[i].month;
    //mean[i].year = data[i].year;
    //sumVal -= data[l].num;
    //l++;
    //}
    else if (r < n - 1) {
      mean[i].num = sumVal / (r - l + 1);
      mean[i].month = data[i].month;
      mean[i].year = data[i].year;
      r++;
      sumVal += data[r].num;
      sumVal -= data[l].num;
      l++;
    }
    else {
      //mean[i].num
      double temp = sumVal / (r - l + 1);
      mean[i].num = temp;
      mean[i].month = data[i].month;
      mean[i].year = data[i].year;
      //      if (data[i].year == 2018 && data[i].month == 06) {
      //fprintf(stdout, "the real value of 2018-06 %f \n", mean[i].num);
      //fprintf(stdout, "keep one decimal place %.1f \n", mean[i].num);
      //}
      sumVal -= data[l].num;
      l++;
    }
  }
}

double findLocalMax(ss_monthly_t * data, size_t n) {
  // WRITE ME
  /* This calculate find the local max value among the value series */
  if (data == NULL) {
    fprintf(stderr, "invalid data input");
    exit(EXIT_FAILURE);
  }
  if (n <= 0) {
    fprintf(stderr, "invalid length");
    exit(EXIT_FAILURE);
  }
  double maxVal = data[0].num;
  double timeStamp = data[0].year + data[0].month / 12.0;
  for (size_t i = 1; i < n; i++) {
    if (data[i].num > maxVal) {
      maxVal = data[i].num;
      timeStamp = data[i].year + data[i].month / 12.0;
    }
  }

  return timeStamp;
}

double calcSsPeriod(double * timeStamps, size_t n) {
  //WRITE ME
  /*
    This function calculate the Sunspots Period
   */
  if (timeStamps == NULL) {
    fprintf(stderr, "invalid timestamp arrray");
    exit(EXIT_FAILURE);
  }
  if (n <= 1) {
    fprintf(stderr, "invalid length");
    exit(EXIT_FAILURE);
  }

  return (timeStamps[n - 1] - timeStamps[0]) / (n - 1);
  //return 0;
}
