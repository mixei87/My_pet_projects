#include "random_arrays.h"

int main() {
  printf("Input number for random: ");
  scanf("%d", &NUM);

  int n;
  printf("Input n: ");
  scanf("%d", &n);

  srand(time(NULL));
  generate_arrays(n);
  return 0;
}
