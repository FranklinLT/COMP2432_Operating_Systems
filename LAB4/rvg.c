// you must compile using the math liabary, i.e. cc -lm random.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h> // in order to use log() function

int arrivalPattern[100];
int servicePattern[100];

int generate(int pattern[], int num, float timespan)
{
  int i;
  float u, r;

  for (i = 0; i < num; i++) {
      u = (float)rand() / RAND_MAX; // generate random number in (0,1]
      r = -log(u)*timespan; // exponential random variable for Poisson events
      pattern[i] = (int)r + 1; // round up to integer; avoid 0 for multiple customers
  }
}

int main()
{
  int seed = 2023;
  int i;

  srand(seed); // do this only once and before using rand() to generate

  // generate patterns for 100 customers
  generate(arrivalPattern,100,5.0); // arriving every 5 time units
  arrivalPattern[0] = 0; // set default arrival time for first customer
  generate(servicePattern,100,4.0); // servicing average 4 time units

  // your computation

  printf("Random arrival pattern generated with seed %d:\n",seed);
  for (i = 0; i < 100; i++) {
      printf("%d ",arrivalPattern[i]);
      if ((i+1) % 30 == 0) printf("\n"); // 30 numbers per line
  }
  printf("\n");
  printf("Random service pattern generated with seed %d:\n",seed);
  for (i = 0; i < 100; i++) {
      printf("%d ",servicePattern[i]);
      if ((i+1) % 30 == 0) printf("\n"); // 30 numbers per line
  }
  printf("\n");
}