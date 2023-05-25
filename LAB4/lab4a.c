// lab 4A
// try to find out how this program can be executed

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  char *name[] = {"Jan", "Feb", "Mar", "Apr", "May", "June",
                  "July", "Aug", "Sept", "Oct", "Nov", "Dec"};
  int yy, mm, dd, numDay;
  int i;

  yy = atoi(argv[1]); // atoi returns an integer
  numDay = atoi(argv[2]);
  if (numDay <= 0 || numDay > 366 || (numDay == 366 && yy % 4 != 0)) {
     printf("Sorry: wrong number of days\n");
     exit(1);
  }

  if (yy % 4 == 0) month[1] = 29;
  for (i = 0; i < 12; i++) {
      if (numDay <= month[i]) break;
      numDay = numDay - month[i];
  }
  mm = i;
  dd = numDay;

  printf("Date is %d %s %4d\n", dd, name[mm], yy);
}