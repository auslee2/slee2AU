/* Lab5.c
 * Samuel Lee
 * Feb 12
 * Purpose: write a program that creates two threads to perform (essentially) the same taks as in lab2.
 */

#include <pthread.h> // for pthread routines
#include <stdlib.h> // for RAND_MAX, srandom, random
#include <time.h> // time()
#include <unistd.h> // for sleep()
#include <stdio.h>
#define NUMBER_OF_THREADS 10
int turn= 0; //global variables for turn
int record= 0; // record which thread last accessed it.
//function prototypes
void *print_division(void*tid);

int main(void)
{  pthread_t threads[NUMBER_OF_THREADS]; // opaque var. not initialized
   int status = 0;		// status returned form pthread_create()
   int i = 0;		// loop counter

   // create a bunch of threads
   for(i=0; i < NUMBER_OF_THREADS; i++) 
   {  printf("Main here. Creating thread %d\n", i);
      status = pthread_create(&threads[i], NULL, print_division, (void *)i);		
      if (status != 0) 
	{ printf("Oops. pthread create returned error code %d\n", status);
	  exit(-1);
	}
   }
   //pthread_join()
   for(i=0;i < NUMBER_OF_THREADS; i++)
   { printf("waiting on thread %d\n",i);
     status = pthread_join(threads[i], NULL);
     printf("thread %d excited\n", i);
   }
   exit(0);
}

void *print_division(void *tid)
{ int num_loops = 0; // init num_loop for int counter
  // print that this thread is starting execution
  printf("thread %d is starting execution\n", (int)tid);
  
  // add the code for #2 so that it will randomly give up its turn  
  /* each thread needs to set the random seed differently, based on it’s tid */
  srandom((unsigned int)time(NULL)+(int)tid);
  /* to randomize execution, threads will yield the processor if they get an even number */
  printf("%d: Starting execution.\n", (int)tid);
  if (((random()/(RAND_MAX/10)) % 2) == 0)
  {  printf("%d:... voluntarily yielding the CPU.\n",(int)tid);
     sched_yield();
  }
 
  // the code for #3 so that it uses busy waiting if it is not it's turn
  while (turn != (int)tid)  // while it's not this process's turn
{     
      // how many times it looped while busy waiting.
      num_loops++;      // busy waiting	
  
}
  
  // (busy waiting is the while loop in #3)
  //print that particular process fid number is entering the critical region
  printf("This particular process %d is entering the critical region. it looped %d times\n", (int)tid, num_loops);
  // then do the tasks in order in #3  
  //Change the global variable to be equal to this process's tid.
  //record is shared resource
  printf("record current value %d\n", record);
  record = (int)tid;
  printf("record changed to %d\n", record); 
  
  //Set the turn variable to be the next process's turn.
  turn = turn + 1; 
 
  //Report that this particular process is exiting the critical region, and what the current value of the global variable is.
  printf(" process %d is exiting the critical region\n", (int)tid);
  //Exit this thread.
  pthread_exit(NULL);
}



