/* Samuel Lee
 * Project 3.c
 * Goal: write a program to simulate a virtual memory system, reading in virtual memory address requests from an input file and writing out physical memory addresses to an output file.  For this project, we will simulate a 16-bit virtual address space, 16KB of main memory, and 2KB page sizes.
 */


//INCLUDE
#include <stdio.h>
#include <string.h> // for strcat()
#include <stdlib.h> // for exit()

//DEFINE
#define SIZE 256        // string size
#define DEBUG 0         // print debug flag
#define TRUE 1
#define FALSE 0
#define sizeV 32          //virtual address int array size
#define sizeP 8           //physical address int array size
#define PAGE_MASK 0xF800  // 1111 1000 0000 0000
#define shift 11 //shift constant
#define OFFSET_MASK 0x07FF  //0000 0111 1111 1111

//struck variable declaration
typedef struct
{ unsigned short int pageframeNum;
  unsigned short int presentAbsentBit;
  
} structure_name; 


//MAIN
int main(int argc, char *argv[])
{ 
  //initialization
  char buffer[SIZE] ="";                       //array shared resource
  FILE* intfileptr = NULL;                             //initialzie in file pointer
  FILE* outfileptr = NULL;
 
  unsigned short int virtaddr;
  int phyaddr[sizeP] ={};
  
  int pageframeCounter = 0;
  int virtTemp; 
  int phyTemp;
  int offset;  
  structure_name virtPage[sizeV]; //current page struct, it gets created everytime programs loops around while
  int j;
  for(j=0;j<32;j++)
  {virtPage[j].pageframeNum = 999;
   virtPage[j].presentAbsentBit = 0;
  }
  int n;
  for(n=0;n<8;n++)
  {phyaddr[n] = 999;
  }
  

  FILE *infileptr =NULL; // pointer to disk
  
  //argv[0]=executable name
  //argv[1]=inputfilename
  //argv[2]=outputfilename
  //Thus if argv[i] for i != 3 is error
  if(argc != 3)
  { if(DEBUG) printf("error case: argc !=3\n");

  }

  //open file
  infileptr = fopen(argv[1],"r");
  outfileptr = fopen(argv[2],"w");
  if(infileptr==NULL)
  { if(DEBUG) printf("error case: infileptr == NULL\n");

  }
  
  //read from file.
  while(fgets(buffer, sizeof(buffer), infileptr)!=NULL)
  { 
    if(pageframeCounter==8)
    { if(DEBUG) printf("virtual page stack is full, reset Counter to 0 and it will eventually overide first one that came in\n");
       pageframeCounter=0;
    }
   
    //debug use
    if(DEBUG) printf("read:%s\n", buffer);
    
    //step 1
    // convert something like 0x6800 into hexidecimal form and store in virtaddr as int arrary
    sscanf(buffer, "%hx", &virtaddr);
    //print virtual address
    printf("Virtual Adress: %x\n", virtaddr);

    //step 2
    // using mask then push >>
    virtTemp = virtaddr & PAGE_MASK; //masking filter out offset
    virtTemp = virtTemp>> shift; //shift it to right side
    
    //phyaddr calculation
    offset = virtaddr & OFFSET_MASK; //masking filter out virtpage
    printf("Offset: 0x%04x\n", offset);
    phyTemp=virtTemp<<shift; //shift virtpage(ex 13) to left side
    phyTemp = phyTemp|offset; //combine with offset;
     
    //step 3,4
    //assigned to pageframe, check pagefault first
    if(virtPage[virtTemp].presentAbsentBit==0) //c will convert hex to int automatically!
    { printf("Page fault! Not in physical memory.\n");
      virtPage[virtTemp].presentAbsentBit =1;
      virtPage[virtTemp].pageframeNum = pageframeCounter;
      //print
      printf("Virtual page %d loaded into page frame %d\n", virtTemp, pageframeCounter);
      //Assigned virtTemp to phyaddr[k]
      phyaddr[pageframeCounter]=virtTemp;
    }
    
    //when page is already exist!
    else
    { printf("Page was already present in physical memory.\n");
      phyaddr[pageframeCounter]=virtTemp;
    }
    //increment pageframeCounter
    pageframeCounter++;
    //print tables
    printf("The page table is:\n");
    int i;
    for(i=0; i<32; i++)
    { printf("[%d] %d %d \t", i, virtPage[i].pageframeNum, virtPage[i].presentAbsentBit);
    }
    printf("The page frames contain these virtual pages:\n");
    for(i=0; i<8;i++)
    { printf("[%d] %d\n", i, phyaddr[i]);
    }
    sprintf(buffer, "0x %04X\n", phyTemp);
    fputs(buffer, outfileptr);
    printf("Writing PHYSICAL MEMORY ADDRESS to file: %s\n",buffer);
   }//end of whileloop  
}
