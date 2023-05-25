// lab 2C1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
void sighandler(int signo) {
 char s[]="INT signal is caught, but future <ctrl>-C will work as usual\n";
 write(1,s,strlen(s)); // print to screen
 signal(SIGINT, SIG_DFL); // reset to default, i.e. terminate process
}
int main() {
 signal(SIGINT, sighandler); // install signal handler
 printf("Program starts\n");
 while (1) { } // an infinite loop
 printf("Program terminates\n");
}
