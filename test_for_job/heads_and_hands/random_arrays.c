#include "random_arrays.h"

void generate_arrays(int n) {
  if (n > 0) {
    arrays *A = (arrays *)malloc(n * sizeof(arrays));
    for (int i = 0; i < n; i++) {
      A->current_pos = i;
      generate_random_array(&A);
    }
  } else {
    printf("Number must be > 0!");
  }
}

void generate_random_array(arrays **A) {
  int m, k, success;

  do {
    m = 1 + rand() % NUM;
    success = 1;
    for (int i = 0; i < (*A)->current_pos && success == 1; i++) {
      if (m == (A[i])->m) {
        success = 0;
      }
    }
  } while (success == 0);

  A[(*A)->current_pos]->p = (int **)malloc(m * sizeof(int *));

  do {
    k = 1 + rand() % NUM;
    success = 1;
    for (int i = 0; i < (*A)->current_pos && success == 1; i++) {
      if (k == (A[i])->k) {
        success = 0;
      }
    }
  } while (success == 0);
  for (int i = 0; i < m; i++) {
    A[(*A)->current_pos]->p[i] = (int *)malloc(k * sizeof(int));
  }
}
