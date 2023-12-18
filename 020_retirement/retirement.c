#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double calcuAmount(double balance, double returnRate, int months, double contribution) {
  printf("Age %3d month %2d you have $%.2f\n", (int)months / 12, months % 12, balance);
  double newBalace = balance + returnRate * balance + contribution;
  return newBalace;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double balance = initial;
  for (int i = startAge; i < working.months + startAge; i++) {
    balance = calcuAmount(balance, working.rate_of_return, i, working.contribution);
  }
  for (int i = startAge + working.months; i < startAge + working.months + retired.months;
       i++) {
    balance = calcuAmount(balance, retired.rate_of_return, i, retired.contribution);
  }
}

int main() {
  retire_info p1Working;
  p1Working.months = 489;
  p1Working.contribution = 1000;
  p1Working.rate_of_return = 0.045 / 12;

  retire_info p1Retired;
  p1Retired.months = 384;
  p1Retired.contribution = -4000;
  p1Retired.rate_of_return = 0.01 / 12;

  retirement(327, 21345, p1Working, p1Retired);

  return 0;
}
