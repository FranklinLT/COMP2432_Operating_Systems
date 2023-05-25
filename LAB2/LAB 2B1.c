// lab 2B1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
void sighandler(int signo) {
 char s[]="SEGV signal is caught, please debug your program\n";
 write(1,s,strlen(s)); // print to screen
 exit(1);
}
int main() {
 int n;
 // you could also try removing the following line
 signal(SIGSEGV, sighandler); // install signal handler
 printf("Please enter a number\n");
 scanf("%d",n); // forget to use address in scanf, i.e. &n
 printf("The number is %d\n",n);
 printf("Program terminates\n");
}