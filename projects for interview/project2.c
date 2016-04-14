/* Project2.c
 * Due Date: March 11th 2016
 * Samuel Lee
 * Purpose:
 * Write a program to use multiple threads to generate random numbers and perform a basic randomness check on these numbers.  Three producer threads will generate random numbers using 3 different methods.  These random numbers will be placed in shared buffers.  Three consumer threads will process the random numbers, performing a basic randomness check.  The parent process will report the results after all threads have exited.
 */

//include packages
#include <stdio.h>
#include <pthread.h>
#include <math.h>    //for pow
#include <stdlib.h>  // for RAND_MAX, srandom, random

//define 
#define MAX 20                              // how many numbers to produce
#define SIZE 10                             //Buffer size
#define TRUE 1 
#define FALSE 0
#define DEBUG 0      // to control printf for debug

//initialize producer and consumer sets with global variables 
pthread_mutex_t the_mutex;
pthread_cond_t condc, condp;
int buffer[SIZE];                           //array shared resource
int front =0;       
int rear = 0;                        //front and rear for enqueue and dequeue
int freq[10]={};

//initialize 2nd set of producer and consumer
pthread_mutex_t the_mutex2;
pthread_cond_t condc2, condp2;
int buffer2[SIZE];                           //array shared resource
int front2 =0;
int rear2 = 0;                        //front and rear for enqueue and dequeue
int freq2[10]={};

//initialize 3rd set of producer and consumer
pthread_mutex_t the_mutex3;
pthread_cond_t condc3, condp3;
int buffer3[SIZE];                           //array shared resource
int front3 =0;
int rear3 = 0;                        //front and rear for enqueue and dequeue
int freq3[10]={};
int pow2 = 0;                         // to avoid repeating same calculation, init pow2 here.


//enque: store input and wrap around when its excess SIZE
void enqueue(int input, int buffer[], int *rear) 
{ buffer[*rear] = input;
  *rear = (*rear+1)% SIZE;

}

//dequeue: store front in temp,remove, wrap around if excess SIZE, return temp
int dequeue(int buffer[], int *front) // do I need int buffer[], *front
{  //remove front
   int temp = buffer[*front];
   //increment front and mod with SIZE
   *front=(*front+1)%SIZE;
   return temp;

}

//random() pseudorandom number generator included in the gcc libraries
int pseudo_random()
{ int number = random();
  return number;

}

//poor random generator
int poor_random()
{  int prandom = 5; //since its poor random that return same number, I init prandom as 5 and just return it.
   return prandom;
}

//RANDU generator Vj+1 = 65539 * Vj mod 2^31
int RANDU(int Vi) 
{  int result=0;
   if(Vi ==0)
   { result=1;
   }
   else  
   {result = 65539*Vi % pow2;
   }
   if(DEBUG) printf("result: %d\n", result);
   return result;

}

//is_full function
int is_full(int front, int rear) //called by producer, check if array is full return T/F
{  int result = 0;
   if(front-1 == rear||((front==0)&&(rear==SIZE-1)))
   {
     result= TRUE;
   }
   else
   {
     result = FALSE;
   }
   if(DEBUG)  printf("is_full called: result-%d\n", result); 
   return result;
}

//is_empty function
int is_empty(int front, int rear) // called by consumer, check if array is empty return T/F
{ if(front == rear)
  { if(DEBUG) printf("is_empty is True\n");
    return TRUE;
  }
  else
  { return FALSE;
    if(DEBUG)  printf("is_empty is False\n");
  }
}

//producer1 for poor random
void *producer(void *ptr)
{ int i;
  for(i=0;i<=MAX;i++)
  { pthread_mutex_lock(&the_mutex);         //get exclusive access to buffer
    while (is_full(front, rear)!=0)                     // need to change while condition for this proj
    {pthread_cond_wait(&condp, &the_mutex);
    }
    //debug
    if(DEBUG)  printf("producer enqueueing\n");

    //call enqueue function here
    enqueue(poor_random(), buffer, &rear); // not sure how 3 random gen would pass value to enque each times.
    pthread_cond_signal(&condc);            //wake up consumer
    pthread_mutex_unlock(&the_mutex);       //release access to buffer
  }
  pthread_exit(0);
}

//consumer1 for poor random
void *consumer(void *ptr)                   //consume data
{ int i;
  int dq_temp;
  for (i=0;i<=MAX;i++)
  { pthread_mutex_lock(&the_mutex);         //get exclusive access to buffer
    while(is_empty(front, rear)!=0)                      //need to change while condition for this proj
    { pthread_cond_wait(&condc, &the_mutex);
    }
    //debuging
    if(DEBUG)  printf("consumer dequeueing\n");
    dq_temp = dequeue(buffer, &front)%10;
    freq[dq_temp]++;
    pthread_cond_signal(&condp);          //wake up consumer
    pthread_mutex_unlock(&the_mutex);     //release access to buffer

  }
  pthread_exit(0);
}

//producer2 for pseudo random
void *producer2(void *ptr)
{ int i;
  pow2 = (int)pow(2,31);
  /* initialize the pseudo-random number generator by setting the seed */
  srandom(1);

  for(i=0;i<=MAX;i++)
  { pthread_mutex_lock(&the_mutex2);         //get exclusive access to buffer
    while (is_full(front2, rear2)!=0)                     // need to change while condition for this proj
    {pthread_cond_wait(&condp2, &the_mutex2);
    }
    //debug
    if(DEBUG)  printf("producer2 enqueueing\n");

    //call enqueue function here      
    enqueue(pseudo_random(), buffer2, &rear2); // not sure how 3 random gen would pass value to enque each times.
    pthread_cond_signal(&condc2);            //wake up consumer
    pthread_mutex_unlock(&the_mutex2);       //release access to buffer
  }
  pthread_exit(0);
}

//consumer2 for pseudo random
void *consumer2(void *ptr)                   //consume data
{ int i;
  int dq_temp;
  for (i=0;i<=MAX;i++)
  { pthread_mutex_lock(&the_mutex2);         //get exclusive access to buffer
    while(is_empty(front2, rear2)!=0)                      //need to change while condition for this proj
    { pthread_cond_wait(&condc2, &the_mutex2);
    }
    //debuging
    if(DEBUG)  printf("consumer dequeueing\n");
    dq_temp = dequeue(buffer2, &front2)%10;
    freq2[dq_temp]++;
    pthread_cond_signal(&condp2);          //wake up consumer
    pthread_mutex_unlock(&the_mutex2);     //release access to buffer

  }
  pthread_exit(0);
}

//producer3 for RANDU
void *producer3(void *ptr)
{ int i;
  int last = 0; //init Vo for RANDU
  for(i=0;i<=MAX;i++)
  { pthread_mutex_lock(&the_mutex3);         //get exclusive access to buffer
    while (is_full(front3, rear3)!=0)                     // need to change while condition for this proj
    {pthread_cond_wait(&condp3, &the_mutex3);
    }
    //debug
    if(DEBUG)  printf("producer3 enqueueing\n");

    //call enqueue function here
    last = RANDU(last);
    enqueue(last, buffer3, &rear3); // not sure how 3 random gen would pass value to enque each times.
    pthread_cond_signal(&condc3);            //wake up consumer
    pthread_mutex_unlock(&the_mutex3);       //release access to buffer
  }
  pthread_exit(0);
}

//consmer3 for RANDU
void *consumer3(void *ptr)                   //consume data
{ int i;
  int dq_temp;
  for (i=0;i<=MAX;i++)
  { pthread_mutex_lock(&the_mutex3);         //get exclusive access to buffer
    while(is_empty(front3, rear3)!=0)                      //need to change while condition for this proj
    { pthread_cond_wait(&condc3, &the_mutex3);
    }
    //debuging
    if(DEBUG) printf("consumer3 dequeueing\n");
    dq_temp = dequeue(buffer3, &front3)%10;
    freq3[dq_temp]++;
    pthread_cond_signal(&condp3);          //wake up consumer
    pthread_mutex_unlock(&the_mutex3);     //release access to buffer

  }
  pthread_exit(0);
}

//Main
int main(int argc, char **argv)
{ //mutex sets of producer1 and consumer1 for poor random
  pthread_t pro;
  pthread_t con; //2 thread variables
  pthread_mutex_init(&the_mutex, 0);
  pthread_cond_init(&condc, 0);
  pthread_cond_init(&condp, 0);
  //debugging
  if(DEBUG)  printf("pthread_cond for condc and condp is init\n");
  pthread_create(&con, 0, consumer, 0); // 2 threads start running
  pthread_create(&pro, 0, producer, 0);
  //debugging
  if(DEBUG)  printf("consumer and producer are created\n");
  pthread_join(pro, 0);
  pthread_join(con, 0);
  // may be printf here?
  //if(DEBUG) 
  //{
  for(int i=0;i<10;i++)
  { printf("Poor random output[%d]:\t %d\n",i ,freq[i]);
  }
  //}
  pthread_cond_destroy(&condc);
  pthread_cond_destroy(&condp);
  pthread_mutex_destroy(&the_mutex);
  
  //mutex sets of producer2 and consumer2 for poor random
  pthread_t pro2;
  pthread_t con2; //2 thread variables
  pthread_mutex_init(&the_mutex2, 0);
  pthread_cond_init(&condc2, 0);
  pthread_cond_init(&condp2, 0);
  //debugging
  if(DEBUG)  printf("pthread_cond for condc2 and condp2 is init\n");
  pthread_create(&con2, 0, consumer2, 0); // 2 threads start running
  pthread_create(&pro2, 0, producer2, 0);
  //debugging
  if(DEBUG)  printf("consumer2 and producer2 are created\n");
  pthread_join(pro2, 0);
  pthread_join(con2, 0);
  // may be printf here?
  //if(DEBUG)
  //{ 
  for(int i=0;i<10;i++)
  { printf("presudo random output[%d]:\t %d\n",i ,freq2[i]);
  }
  //}
  pthread_cond_destroy(&condc2);
  pthread_cond_destroy(&condp2);
  pthread_mutex_destroy(&the_mutex2);

  //mutex sets of producer3 and consumer3 for poor random
  pthread_t pro3;
  pthread_t con3; //2 thread variables
  pthread_mutex_init(&the_mutex3, 0);
  pthread_cond_init(&condc3, 0);
  pthread_cond_init(&condp3, 0);
  //debugging
  if(DEBUG)  printf("pthread_cond for condc3 and condp3 is init\n");
  pthread_create(&con3, 0, consumer3, 0); // 2 threads start running
  pthread_create(&pro3, 0, producer3, 0);
  //debugging
  if(DEBUG)  printf("consumer3 and producer3 are created\n");
  pthread_join(pro3, 0);
  pthread_join(con3, 0);
  // may be printf here?
  //if(DEBUG) 
  //{ 
  for(int i=0;i<10;i++)
  { printf("RANU output[%d]:\t %d\n",i ,freq3[i]);
   
  }
   //}
  pthread_cond_destroy(&condc3);
  pthread_cond_destroy(&condp3);
  pthread_mutex_destroy(&the_mutex3);

}
