/* Samuel Lee
 * Thu Apr 28 2016
 * Purpose:Implement a utility that creates a backup directory and copies a file into that directory, using a single command-line argument.  For example, the user would enter: ./a.out   filename
 * where filename is the name of the file.  The program will create a backup directory and copy the file to this directory.  If successful, no output is needed (following the Linux philosophy).  Only warning messages or error messages need to be printed (when DEBUG is turned off, that is).
*/

#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>     /* malloc */ 
#include <string.h>     /* string libraries */
#include <sys/types.h>  /* for fork */
#include <unistd.h>     /* for fork and execvp */

#define BACKUP_DIR_NAME "backup"
#define TRUE 1
#define FALSE 0
#define SIZE 256        // string size
#define MAX_NUM_ARGS 256
#define MAX_NUM_CHAR 256
#define BUFFER_LEN 256 
#define DEBUG 0
#define DEBUG_MAIN 0
/**** errors returned by the shell ****/
#define OUT_OF_MEMORY_ERROR 40 

int flag = 0;

int main(int argc, char *argv[])
{  
   char **input_args=NULL;  	/* args for user command */
   //initialization
   int i;
   int pid=0;			/* process ID, used with fork() */
   int retval=0;		/* return value from execvp() */
   int errorval=0;		/* return value from waitpid() */
   int childstatus=0;		/* value returned from child for waitpid() */
   int next = 0;                /* i+1 for forloop*/
   int counter =0;              /* counter for input array*/
   int charCount = 0;           /* char counter for 2nd dimension array*/

   int DEBUG_print = TRUE;      /* initialize Print check as true*/
   int justEnter = FALSE;       /* initialize flag for case when user just type enter*/
   char buffer[SIZE] =""; 	                        //array shared resource
   // FILE* intfileptr = NULL;                             //initialzie in file pointer
   // FILE* outfileptr = NULL;


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

  DIR *dp; // pointer to a directory
  struct dirent *ep; //dirent pointer direct entry
  // open directory file
  dp = opendir("./"); // current directory
  if(dp != NULL) 
  {  // opened successfully
     // print each entry
     while ((ep = readdir(dp))!=NULL) 
     { if(strcmp((ep -> d_name), BACKUP_DIR_NAME)==0) // -> follows structure pointer and access part of the structure
       {  printf("directory already exist\n");
          //ep->d_name = "backup.1";//how can I change ep->d_name to something else?
          flag = TRUE;
       }
       //check if the directory does not exist
       if(flag == FALSE)
       { mkdir(BACKUP_DIR_NAME, S_IRWXU);
       }
     }
     closedir(dp);
  }
  else 
  { printf("file not opened \n");
  }
   //need to build input args[0]
  FILE *infileptr =NULL; // pointer to disk
  
  //argv[0]=executable name
  //argv[1]=inputfilename
  //argv[2]=outputfilename
  //Thus if argv[i] for i != 3 is error
  if(argc != 3)
  { if(DEBUG) printf("error case: argc !=3\n");
  }

  //open file
  //infileptr = fopen(argv[1],"r");
  //outfileptr = fopen(argv[2],"w");
  input_args[0] = strcpy(input_args[0], "cp"); //connecting this cp can be hard code for our purpose
  input_args[1] = strcpy(input_args[1], argv[1]);
  input_args[2] = strcpy(input_args[2], strcat("./backup/", strcat(argv[1],".backup")));
  input_args[3] = NULL; //it will always be NULL
  
  if(infileptr==NULL)
  { if(DEBUG) printf("error case: infileptr == NULL\n");

  }    

 
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
  {    retval = execvp(input_args[0], input_args); //what needs to be done to execute all command, do I need to execute all the argv[1-4]?
       if(retval!= 0)
       { if(justEnter==TRUE)
         { //reset flag and  dont exit out so while loop catches
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
return 0;
} 
