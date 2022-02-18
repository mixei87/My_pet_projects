#include "random_arrays.h"

int main() {
  int n;
  printf("Input n:\n");
  if (scanf("%d", &n) == 1) {
    srand(time(NULL));
    NUM = n * 2;
    generate_arrays(n);
  } else {
    printf("Wrong input!");
  }
  return 0;
}
