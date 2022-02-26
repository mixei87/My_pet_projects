#include "random_arrays.h"

arrays* generate_arrays(int n) {
  arrays* arr = NULL;
  if (n > 0 && n < INT_MAX / 2) {
    srand(time(NULL));
    NUM = n * 2;  // I think that it enough
    arr = (arrays*)malloc(sizeof(arrays) * n);
    if (arr != NULL) {
      arrays hash_table;
      hash_table.num = NUM;
      hash_table.vector = (int*)calloc(hash_table.num, sizeof(int));
      if (hash_table.vector != NULL) {
        for (int i = 0; i < n; i++) {
          create_array(i, arr, &hash_table);
          fill_array(&arr[i]);
          fast_sort(&arr[i], 0, arr[i].num - 1, ((i + 1) % 2) * 2 - 1);
        }
        free(hash_table.vector);
      } else {
        printf("Memory isn't allocate!");
      }
    } else {
      printf("Memory isn't allocate!");
    }
  } else {
    printf("Number must be > 0 and < INT_MAX/2 !");
  }
  return arr;
}

void create_array(int count, arrays* arr, arrays* hash_table) {
  int status, n;
  do {
    n = 1 + rand() % NUM;
    status = check_size_arr(n, hash_table);
  } while (status == 1);
  write_size_arr(n, hash_table);
  arr[count].num = n;
  arr[count].vector = (int*)malloc(n * sizeof(int));
}

int check_size_arr(int n, arrays* hash_table) {
  int status = 0, i = n % hash_table->num;
  for (; status == 0 && hash_table->vector[i] != 0;
       i = (i + 1) % hash_table->num) {
    if (hash_table->vector[i] == n + 1) status = 1;
  }
  return status;
}

void write_size_arr(int n, arrays* hash_table) {
  int i = n % hash_table->num;
  for (; hash_table->vector[i] != 0; i = (i + 1) % hash_table->num) {
    ;
  }
  hash_table->vector[i] = n + 1;
}

void fill_array(arrays* arr) {
  for (int i = 0; i < arr->num; i++) {
    arr->vector[i] = rand() % NUM;
  }
}

void fast_sort(arrays* arr, int left, int right, int dir) {
  if (left < right) {
    int L = left, R = right;
    int B = arr->vector[(left + right) / 2];
    while (L <= R) {
      while (arr->vector[L] * dir < B * dir) {
        L++;
      }
      while (arr->vector[R] * dir > B * dir) {
        R--;
      }
      if (L <= R) {
        int tmp = arr->vector[R];
        arr->vector[R] = arr->vector[L];
        arr->vector[L] = tmp;
        L++;
        R--;
      }
    }
    fast_sort(arr, left, R, dir);
    fast_sort(arr, L, right, dir);
  }
}

void remove_arrays(arrays* arr, int n) {
  for (int i = 0; i < n; i++) {
    free(arr[i].vector);
  }
  free(arr);
}
