// lab 4B
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int  childid, myid, parentid, cid;
  int  val;

  val = 1;
  myid = getpid();
  printf("My id is %d, value is %d\n",myid,val);
  childid = fork();
  if (childid < 0) { // error occurred
     printf("Fork Failed\n");
     exit(1);
  } else if (childid == 0) { // child process
     myid = getpid();
     parentid = getppid();
     printf("Child: My parentid is %d, childid is %d\n",parentid,childid);
     printf("Child: My id is %d, value is %d\n",myid,val);
     val = 12;
     printf("Child: My id is %d, value is %d\n",myid,val);
     sleep(4);
     printf("Child: My id is %d, value is %d\n",myid,val);
     val = 13;
     printf("Child: My id is %d, value is %d\n",myid,val);
     sleep(4);
     printf("Child: My id is %d, value is %d\n",myid,val);
     printf("Child: I %d completed\n",myid);
     exit(0);
  } else { // parent process
     printf("Parent: My childid is %d\n",childid);
     printf("Parent: My id is %d, value is %d\n",myid,val);
     val = 2;
     printf("Parent: My id is %d, value is %d\n",myid,val);
     sleep(4);
     printf("Parent: My id is %d, value is %d\n",myid,val);
     val = 3;
     printf("Parent: My id is %d, value is %d\n",myid,val);
     sleep(4);
     printf("Parent: My id is %d, value is %d\n",myid,val);
     cid = wait(NULL);
     printf("Parent: Child %d collected\n",cid);
     exit(0);
  }
}