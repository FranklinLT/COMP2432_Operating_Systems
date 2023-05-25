// lab 2C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
void sighandler(int signo) {
 char s[]="INT signal is caught, program terminated by signal handler\n";
 write(1,s,strlen(s)); // print to screen
 exit(1);
}
int dosomething(int n) { // use up some time
 int i;
 for (i = 0; i < 1000000000; i++) {}
 printf("%d\n",n);
}
int main() {
 int i;
 signal(SIGINT, sighandler); // install signal handler
 printf("Program starts\n");
 for (i = 1; i <= 10; i++) dosomething(i);
 printf("Program terminates\n");
}
