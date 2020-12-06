#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algorithms.c"

#define PAGEREF_MAX 40

// converts a string of single digits separated by a comma to an array of ints at *str
void parseInput(int *pageRefs, char *input);

// runs Fist-In-First-Out Algorithm on array of integers
// returns number of page faults
int FIFO(int *str);

// runs Last-Recently-Used Algorithm on array of integers
// returns number of page faults
int LRU(int *str);

// runs Optimal Algorithm on array of integers
// returns number of page faults
int Optimal(int *str);

int Optimal2(int *str);



// Globals
int pageRef[PAGEREF_MAX]; // Page Reference String as an array of ints

int main(int argc, char *argv[]) {

  // verify input

  if (argc == 1) { // generate random pageRef if no numbers are given
    printf("Generating random page reference list: \n");
    for (int i ; i < PAGEREF_MAX ; i++){
      pageRef[i] = rand() % 10;
      printf("%d ",pageRef[i]);
    }
    printf("\n");
  }

  else if (argc < 3) { // parse inputted pageRef string
    parseInput(pageRef, argv[1]);
    for (int i=0 ; i < PAGEREF_MAX ; i++)
      printf("%d ", pageRef[i]);
    printf("\n");
  }

  else {
    printf("Error: Execute as './vmmpr <num1, num2,... num(n)' for up to 40 numbers\n");
    exit(0);
  }



  // Run Algorithms
  printf("%d Faults detected with FIFO\n", FIFO(pageRef));
  printf("%d Faults detected with LRU\n", LRU(pageRef));
  printf("%d Faults detected with Optimal\n", Optimal(pageRef));


}

void parseInput(int *pageRefs, char *input)
{
  int index = 0;
  char *num;
  num = strtok(input, ",");
  while (num != NULL && index < 40){
    pageRefs[index++] = atoi(num);
    num = strtok(NULL, ",");
  }

  while (index < 40)
    pageRefs[index++] = -1;
}
