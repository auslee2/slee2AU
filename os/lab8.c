/* lab8.c
 * Samuel Lee
 * April 8 2016
 * Purpose:  to demonstrate unit testing for a function that we wrote.
 */

#include <stdio.h>
#include <math.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0
#define EPSILON 0.001 // a small number, used in unit testing


//function prototypes
int is_even(int num);
int test_is_even();
double convert(double degrees);
double test_convert();

//main
int main()
{ int result = FALSE; // result of unit tests
  
  //run tests
  printf("Calling unit tests for function is_even().\n");
  result = test_is_even();
  if(result == TRUE)
  { printf("All tests passed!\n");
  }
  else
  { printf("failed on first unit tests test_is_even(). exit.\n");

  }
  test_convert(); //test convert()
  // exit
  printf("all test passed.\n");
  return 0;

}

/** mod a given number by two, if remainder is 0 return ture, else false.
*   @param num the number to use in the calculation
*   @return (num%2);
*/

int is_even(int num)
{  return (num%2);

}

/** run unit tests for test_is_even()
*  @param none
*  @return true if all tests succed. abort if tests fail (uses assert()).
*/

int test_is_even()
{ //run unit tests
  assert(is_even(4)==0);
  assert(is_even(6)==0);
  assert(is_even(8)==0);
  assert(is_even(10)==0);
  assert(is_even(12)==0);
  
 // passed all tests!
 return TRUE;
}

/** convert a given number from degrees to radians
*   @param degrees the number to use in calculation in term of degree.
*   @return (radians = degrees*(2.0*M_PI/360.0));
*/

double convert(double degrees)
{ double radians = degrees*(2.0*M_PI/360.0);
  return radians;
}

/** run unit tests for convert()
*  @param none
*  @return true if all tests succeed. abort if tests fail(uses asserts())
*/

double test_convert()
{ assert( fabs(convert(0) - 0 ) <= EPSILON);
  assert( fabs(convert(45) - 0.785398) <= EPSILON);
  assert( fabs(convert(90) - 1.5708) <=EPSILON);
  assert( fabs(convert(180) - 3.14159) <=EPSILON);
  assert( fabs(convert(142) - 2.47837) <=EPSILON);
  assert( fabs(convert(360) - 6.28319) <=EPSILON);
  
  // passed all tests!
  return TRUE;
}
