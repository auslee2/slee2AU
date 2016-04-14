/*i project1-startercode.c 
* Feb 6, 2016
* Samuel Lee 
* Purpose:  to gain experience with process creation, and the execvp command 
*           by writing a simple shell.  */ 

#include <stdio.h> 
#include <stdlib.h>     /* malloc */ 
#include <string.h>     /* string libraries */
#include <sys/types.h>  /* for fork */
#include <unistd.h>     /* for fork and execvp */

#define TRUE 1
#define FALSE 0

/**** debugging printf statements ****/
#define DEBUG_MAIN 0

/**** errors returned by the shell ****/
#define OUT_OF_MEMORY_ERROR 40 

/**** array limits ****/
#define MAX_NUM_ARGS 256
#define MAX_NUM_CHAR 256
#define BUFFER_LEN 256 

int main(void)
{  char **input_args=NULL;  	/* args for user command */
   int num_args=0;		/* number of arguments read (including 0th) */
   int i=0;			/* iteration counter */
   int pid=0;			/* process ID, used with fork() */
   int retval=0;		/* return value from execvp() */
   int errorval=0;		/* return value from waitpid() */
   int childstatus=0;		/* value returned from child for waitpid() */
   int next = 0;                /* i+1 for forloop*/
   int counter =0;              /* counter for input array*/
   int charCount = 0;           /* char counter for 2nd dimension array*/
   char buffer[BUFFER_LEN] = "";/* initialize char buffer array length 256*/
   int DEBUG =0;                /* initialize flag*/
   int DEBUG_print = TRUE;      /* initialize Print check as true*/
   int justEnter = FALSE;       /* initialize flag for case when user just type enter*/

/*while(1)
 {*/
   /* display the prompt */
   printf("oyster-shell>");

   /**** initialize array of strings for input arguments ****/
   /* we need to do this each time, since execvp requires a null pointer
    * at the end of the argument list */
   /* first check to see if we need to free the memory */
   if (input_args != NULL)
   {  /* free the memory for each array */
      for (i=0; i<MAX_NUM_ARGS; i++)
      {  /* note:  for the one with the NULL pointer, free just returns */
         free(input_args[i]); 
      } 
      /* free the memory for input_args array of arrays */
      free(input_args);
   }
   /* now allocate the memory */
   input_args=(char **)malloc(sizeof(char*) * MAX_NUM_ARGS);
   /* check return value for error */
   if (input_args == NULL)
   {  printf("Oyster Shell:  Fatal out of memory error.\n");
      exit(OUT_OF_MEMORY_ERROR);
   }
   for (i=0; i<MAX_NUM_ARGS; i++)
   {  /* malloc memory for array of arguments */
      input_args[i]=(char*)malloc(sizeof(char) * BUFFER_LEN); 
      /* check return value for error */
      if (input_args[i] == NULL)
      {  printf("Oyster Shell:  Fatal out of memory error.\n");
         exit(OUT_OF_MEMORY_ERROR);
      }
   } 

   /**** get the input, break into arguments ****/
   //write fgets to read line to buffer
   fgets(buffer, sizeof(buffer), stdin);
   // error handling for case where input is over 256 char
   
   //reset counter and charCount to 0.
   counter=0;
   charCount=0;
   
   //forloop to filter buffer
   for(i=0; i<strlen(buffer);i++)
   { //making sure next is always counter+1
     next = counter+1; 

     //if buffer[i] is a space or \t
     if(buffer[i] == ' '|| buffer[i] == '\t')
     { //when there is space and there was no letter before this
       if(DEBUG == FALSE)
       { //just skip untill we know there was a letter before buffer[i]
       }
       else if(DEBUG == TRUE)
       { 
         if(buffer[i+1]=='\n')
         { input_args[counter][charCount] = '\0';
           free(input_args[next]);
           input_args[next] = NULL;
           charCount =0;
           break;
         }
         else
         { counter++;
           charCount = 0;
           DEBUG = FALSE;
          }
       }  
       else
       { //error handling
         printf("DEBUG flag is not expected value %d\n", DEBUG);
       }
     }

     //if it is a \n we are done do execvp()
     else if(buffer[i] == '\n')
     { if(counter== 0 && charCount == 0)
       { // if \n is the very first and only command.
         justEnter = TRUE;
         printf("handling Empty command\n");
       }
       else
       { input_args[counter][charCount] = '\0';
         free(input_args[next]);
         input_args[next] = NULL;
         charCount =0;
         //how to be done?
         break;
       }
     }
     //else(a leter or #), copy to input_args
     else
     { //copy buffer[i] to input_args array and increament charCount
       input_args[counter][charCount] = buffer[i];
       charCount++;
       DEBUG = TRUE;
     }

   }   
   //to check if input_args is right pic on board
   if(DEBUG_print==TRUE)
   { for(i=0;i<5;i++)
     { printf("input_args[%d] = --%s--\n", i, input_args[i]);

     }
   }

   /* see if they typed exit, if so, quit the shell */
   if (strcmp(input_args[0], "exit")==0)
     exit(0);

   /**** execute the command using fork and execvp ****/
   
   /* based on Figure 10-7 in the text */
  
    /* fork off a child process */
    pid = fork();

      /* check for error after fork */
      if(pid<0)
      {printf("Error pid returned less than 0\n");
      }
      /* if this is the parent .... wait on the child */
      else if(pid == 0)
      {printf("I am the parent. Ready to wait on the child.\n");
       pid = waitpid(-1,&childstatus,0);
       printf("child %d returned a value of %x in hex.\n",pid, childstatus);
      }
      /* if this is the child .. call execvp */
      else if(pid > 0)
      { retval = execvp(input_args[0], input_args);
        if(retval!= 0)
        { if(justEnter==TRUE)
          { //  reset flag and  dont exit out so while loop catches
            justEnter = FALSE;
            printf("flag working fine. Empty command is handled.\n");
            exit(2);
          }
          else
          { printf("%s error command not found\n", input_args[0]);
            exit(1);
          }
        }
      }
 /* }*/
} 
