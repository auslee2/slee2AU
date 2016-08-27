// lab06starter.c 
// Jennifer Coy 
// Mar 2016 
// Purpose:  to learn how to use structs and bit operators in C

#include <stdio.h>
#include <string.h> // for strcat()
#include <stdlib.h> // for exit()

#define SIZE 256        // string size

//struck variable declaration
typedef struct {
    char month[SIZE];
    int date;
    int year;
} structure_name;



// declare the struct up here, so we can use it anywhere

// function prototype
char *uint_as_bin(unsigned int num, char *buffer);


int main(void) {
    unsigned short int num = 42;
    unsigned short int num2 = 0xF0F0;
    unsigned short int result = 0;
    unsigned short int num3 = 0x20;
    unsigned short int num4 = 0x09;
    char buffer[SIZE]=""; //out put for binary
    //delcare a variable of struct type
    // assign as initialize my_birth
    structure_name my_birth = {"Oct", 16, 1991};
    // initialize and assign later
    structure_name sis_birth = {"Jan", 25, 1993}; 
    
    while(num!=0)
    {  // demonstrate how to use the uint_as_bin() function
       printf("%4d in hex is %04X which is binary %s\n", 
           num, num, uint_as_bin(num, buffer));
       num = num>>1;
    }
    num = 0xDDDD;
    result = num|num2;
    printf("Logical OR: F0F0 in hex is %04X which is binary %s\n",
            result, uint_as_bin(result, buffer));
    result = num&num2;
    printf("Logical AND: F0F0 in hex is %04X which is binary %s\n",
            result, uint_as_bin(result, buffer));
    printf("Han Na Lee: month:%s date:%d year:%d\n", sis_birth.month, sis_birth.date, sis_birth.year);
    printf("Samuel Lee: month:%s date:%d year:%d\n", my_birth.month, my_birth.date, my_birth.year);
    result = num3|num4;
    printf("Logical AND: Ox20 and Ox09 in hex is %04X which is binary %s\n",
            result, uint_as_bin(result, buffer)); 
    
    // exit program
    return 0;
}

////////// UINT_AS_BIN //////////
// convert an unsigned int number to a binary representation as a string
// @param  num is the number imput
// @param  buffer is the string output (already allocated)
// @return the pointer to the buffer, so that we can print it directly 
//         from the function call
// convert an unsigned int number to a binary representation as a string
char *uint_as_bin(unsigned int num, char *buffer) {
    int num_bits = 0;       // number of bits in the result
    unsigned int mask = 0;  // the "mask", which is a 1 in only one bit location
    int i = 0;              // loop counter

    // error check first!
    if (buffer == NULL) {
        printf("Error -- uint_as_bin requires string to be allocated before function call.\n");
        exit(42);  // quit program with an error
    }

    // figure out the bit mask that we need
    num_bits = sizeof(num) * 8; // 8 bits per byte, sizeof() returns bytes
    // we want a 1 in the left-most place in the mask:  
    // 0b1000 0000 0000 0000 0000 0000 0000 0000
    mask = 1<<(num_bits-1);

    // loop through each bit, adding it to the output
    // note that we need to move through the number from most 
    // significant bit to least, in order to print it out correctly
    for (i=0; i<num_bits; i++) {
        // (as a side note that & has lower precedence than ==, 
        // so without the () the num==0 is evaluated first)
        // if we bitwise AND (&) the number with the mask...
        if ((mask & num) == 0) {
            // if we get a zero, there is a zero in that spot in the num
            buffer[i] = '0';
        } else {
            // if we get anything else (a power of two), then there is a 1 here
            buffer[i] = '1';
        }
        // now shift the mask to the right, to grab the next bit
        mask=mask>>1;
    }

    // add a null terminator to the string
    buffer[i] = '\0';

    // return the pointer to the string, so we could print it directly
    // using print("%s", uint_as_bin(a_num, a_buffer));
    return buffer;
}
