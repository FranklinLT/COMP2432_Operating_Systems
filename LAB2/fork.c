#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
 int childid;
childid = fork(); /* fork a child process */
if (childid < 0) { /* error occurred */
printf("Fork Failed\n");
exit(1);
} else if (childid == 0) { /* I am child process */
execl("/bin/ls", "ls", NULL);
} else { /* I am parent process */
/* some parent program code */
/* parent will wait for the child to complete */
wait(NULL);
printf("Child Complete\n");
exit(0);
}
}
