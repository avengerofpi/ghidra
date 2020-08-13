#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

/* 
Pick two random ints in range [2, 20].
Then pick random ints until a value is found that is a multiple of both.
Log and keep track of certain data to produce output roughly of the form:

Modulus 1: <1st modulus>
Modulus 2: <2nd modulus>

Failure 001: <1st failure, if any>
Failure 002: <2nd failure, if any>
...<skipped lines>...
Failure xyz: <last failure, if any>

Total number of failures: %i
Total sum of failures:    %i
Total sum of failures mod <1st modulus>:    %i
Total sum of failures mod <2nd modulus>:    %i

Success: <first success>
*/

void init_rand_with_time() {
  /* Initialize random seed using current system time */
  srand((unsigned) time(NULL));
}

void init_rand() {
  /* Initialize random seed */
  init_rand_with_time();
}

unsigned int get_random_constrained_uint(unsigned int a, unsigned int b) {
  /* Get random unsigned int between two values. */
  unsigned int min, max, diff;
  unsigned int ret = a; // default if a == b

  // Figure out min/max of bounds
  if (a <= b) { min = a; max = b; }
  else        { min = b; max = a; }
  diff = max - min;
  if (diff > 0) {
    ret = min + (rand() % diff);
  }

  return ret;
}

unsigned int rand_v() {
  const unsigned int MAX_RAND_V = 1000;
  return get_random_constrained_uint(1, MAX_RAND_V);
}

void init_moduli(unsigned int *m1, unsigned int *m2, unsigned int *MOD_MIN, unsigned int *MOD_MAX) {
  /* Initilize the moduli variables */
  *MOD_MIN =  2;
  *MOD_MAX = 20;
  *m1 = get_random_constrained_uint(*MOD_MIN, *MOD_MAX);
  *m2 = get_random_constrained_uint(*MOD_MIN, *MOD_MAX);
  return;
}

void get_next_v(unsigned int *v,
    unsigned int m1, unsigned int m2,
    unsigned int *vm1, unsigned int *vm2) {
  /* Generate next v and compute its modular reductions */
  *v = rand_v(); *vm1 = *v % m1; *vm2 = *v % m2;
}

void print_v_analysis(
    bool success_status,
    unsigned int v, 
    unsigned int m1,
    unsigned int m2,
    unsigned int vm1,
    unsigned int vm2,
    unsigned int *fail_num) {
  /* Print out details of current v; update fail_num value */
  // If successful 
  if (success_status) {
    printf("Success: %3i = %i * %i = %i * %i\n", v, v / m1, m1,  v / m2, m2);
  } else { // If failed
    printf("Failure: %03i: %3i (mod %2i = %2i) (mod %2i = %2i)\n", ++(*fail_num), v, m1, vm1, m2, vm2);
  }
}

int main() {
  // Declare variables
  unsigned int m1, m2, MOD_MIN, MOD_MAX; // moduli
  unsigned int fail_num, fail_sum; // failure stats
  unsigned int v, vm1, vm2; // current random value and its modular reductions
  bool success_status = false;

  // Initialize randomness
  init_rand();
  init_moduli(&m1, &m2, &MOD_MIN, &MOD_MAX);

  // Print modulus details
  printf("Modulus 1: %2i\n", m1);
  printf("Modulus 2: %2i\n", m2);
  printf("\n");

  // Look for a value that is a multiple of both m1 and m2
  fail_num = 0;
  get_next_v(&v, m1, m2, &vm1, &vm2);
  while (v % m1 != 0 || v % m2 != 0) {
    print_v_analysis(success_status, v, m1, m2, vm1, vm2, &fail_num);
    fail_sum += v;
    get_next_v(&v, m1, m2, &vm1, &vm2);
  }
  printf("\n");
  printf("Total number of failures: %i\n", fail_num);
  printf("Total sum of failures: %i\n", fail_sum);
  printf("Total sum of failures mod %2i: %2i\n", m1, fail_sum % m1);
  printf("Total sum of failures mod %2i: %2i\n", m2, fail_sum % m2);

  // Success!
  success_status = true;
  printf("\n");
  print_v_analysis(success_status, v, m1, m2, vm1, vm2, &fail_num);

  // We are done.
  return(0);
}

