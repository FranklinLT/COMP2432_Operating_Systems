// lab 2A
#include <stdio.h>
int main(int argc, char* argv[])
{
 int n, i;
 n = atoi(argv[2]);
 for (i = 0; i < n; i++) {
 sleep(2);
 printf("program name: %s, argument: %s, output: %d\n",argv[0],argv[1],i);
 }
}