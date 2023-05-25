// lab 4D
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int  childid, myid, parentid, cid;
  int  ret, cret;

  myid = getpid();
  childid = fork();
  if (childid < 0) { // error occurred
     printf("Fork Failed\n");
     exit(1);
  } else if (childid == 0) { // child process
     myid = getpid();
     parentid = getppid();
     printf("Child: My id is %d, my parentid is %d\n",myid,parentid);
     // do some calculation here
     ret = 3; // just an example here
     exit(ret);
  } else { // parent process
     printf("Parent: My childid is %d\n",childid);
     cid = wait(&cret);
     printf("Parent: Child %d collected\n",cid);
     printf("Parent: Child returning value %d vs %d\n",cret,WEXITSTATUS(cret));
     exit(0);
  }
}