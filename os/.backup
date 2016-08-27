/* twoproc.c
 * Samuel Lee
 * Jan 29th 2016
 * Purpose: Demonstate how to create a new process, using fork, waitpad, exit
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define CHILD 0

int main(void)
{ int pid = 0; /* proess id: am I the parent or the child? */
  int childvalue=0; /* what the child returns to the parent */
  int nonezero = 5; /* initialize values for division*/
  int zero = 0;
  int result =0;
 
  /* create a child*/
  pid = fork();

  /* if I am the parent, print a message, and wait on the child */
  if (pid!= CHILD)
  { printf("I am the parent. Ready to wait on the child.\n");
    pid = fork();
    if (pid != CHILD)
    { pid = waitpid(-1, &childvalue, 0);
      printf("Child %d returned a value of %x in hex.\n", pid, childvalue);
      pid = waitpid(-1, &childvalue, 0);
      printf("child %d returned a value of %x in hex.\n", pid, childvalue);
      /* exit this process */
      exit(0);
    }
    else /*this is the second child, print a message and perform a division where variable contents do NOT cause a divide by zero error*/
    { printf("I am the second child. performing a division that is NOT cause a divide by zero error.\n");
    /*perform division*/
    result = 10 / nonezero;
    /*print the result*/
    printf("10 / 5 = %d\n", result);
    /*exit cleanly*/
    exit(2);  
    }
  }
  else /* this is the first child,print a message stating that this is the first child, attempt to perform a division, but the variable contents cause  a divide by zero error*/
  { printf("I am the first child. performing a division that cause  a divide zero error.\n");
    /*attempt to perform division*/
    result = nonezero/zero;
    /*try to print the result*/
    printf(" 5 / 0 = %d\n", result);
    /*try to exit cleanly*/
    exit(1);
  }
  

}
