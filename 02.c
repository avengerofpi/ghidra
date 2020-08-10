#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Bitwise majority vote of 3 random ints

int main() {
  // Declare variables
  int a, b, c, mv;

  // Initialize random seed using time
  srand((unsigned) time(NULL));

  // Get random values and calculate the majority vote
  a = rand();
  b = rand();
  c = rand();
  mv = (a & b) ^ (a & c) ^ (b & c);

  // Print out the random values and the majority vote, in hex
  printf("%08x\n", a);
  printf("%08x\n", b);
  printf("%08x\n", c);
  printf("--------\n");
  printf("%08x\n", mv);
  return(0);
}
