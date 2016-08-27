/* Lab4.c
 * Samuel Lee
 * Feb 12
 * Purpose: write a program that creates two threads to perform (essentially) the same taks as in lab2.
 */

#include <pthread.h> // for pthread routines
#include <stdlib.h> // for RAND_MAX, srandom, random
#include <time.h> // time()
#include <unistd.h> // for sleep()
#include <stdio.h>
#define NUMBER_OF_THREADS 2

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
   status = pthread_join(threads[0], NULL);
   status = pthread_join(threads[1], NULL);
   pthread_exit(NULL);
}

void *print_division(void *tid)
{ int maximum_time = 0; // initialize max time
  int number = 0; // initialize int for randomized number for sleep.
  int result = 0; // initialize int for division result.
  int zero = 0;

  /* initialize the pseudo-random number generator by setting the seed */
  srandom((unsigned int)time(NULL)+(int)tid);
	
  /* pick a random number less than the maximum_time */
  maximum_time = 4;  /* 4 seconds maximum wait */
  number = random()% maximum_time;
   	
  /* wait this amount of time, in seconds */
  printf("Thread %d sleeping %d seconds.\n",(int)tid, number);
  sleep(number);
	
  //if statement if thats fisrt do this else do that
  if(tid == 0)
  {  //print first child attemp division
     printf("I am the first child, attemping division.\n");
	 
     //division
     result = 84/2;
     printf("result for division 84/2 = %d\n", result);
    
     //exiting
     pthread_exit(NULL);
  }
  else  //second child
  {  printf("I am the second child, attempting division.\n"); 
     result = 84/ zero;
     printf("result for division 84/0 = %d\n", result);
     pthread_exit(NULL);
  }
}



