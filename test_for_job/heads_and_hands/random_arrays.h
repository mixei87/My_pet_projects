#ifndef RANDOM_ARRAYS_H_
#define RANDOM_ARRAYS_H_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int NUM;  // how many elements (max) need generate
typedef struct array {
  int num;
  int* vector;
} arrays;

// n > 0
arrays* generate_arrays(int n);
void create_array(int count, arrays* arr, arrays* hash_table);
int check_size_arr(int n, arrays* hash_table);
void write_size_arr(int n, arrays* hash_table);
void fill_array(arrays* arr);
// direction (1: ascending, -1: descending)
void fast_sort(arrays* arr, int left, int right, int dir);
void remove_arrays(arrays* arr, int n);

#endif  // RANDOM_ARRAYS_H_
