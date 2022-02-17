#ifndef RANDOM_ARRAYS_H_
#define RANDOM_ARRAYS_H_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int NUM;  // how many elements (max) need generate

// typedef struct row {
//   // for generate rows
//   int *m;
// } rows;

typedef struct array_of_array {
  // for generate arrays
  int current_pos;
  int **p;
  // rows r;
  // m - size of rows
  int m;
  // k - size of columns
  int k;
} arrays;

// n > 0
void generate_arrays(int n);
void generate_random_array(arrays **A);
#endif  // RANDOM_ARRAYS_H_
