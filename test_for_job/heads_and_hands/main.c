#include "random_arrays.h"

int main() {
  int n;
  printf("Input n: ");
  if (scanf("%d", &n) == 1) {
    arrays* arr = generate_arrays(n);
    if (arr != NULL) {
      remove_arrays(arr, n);
    }
  } else {
    printf("Wrong input!");
  }
  return 0;
}
