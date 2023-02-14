// https://contest.yandex.ru/contest/45468/problems/4/
#include <iostream>

using namespace std;

int main() {
  int n, k, row1, seat1;
  cin >> n;
  cin >> k;
  cin >> row1;
  cin >> seat1;
  // 11 5 3 2
  int index1 = (row1 - 1) * 2 + seat1 - 1;        // 5
  int index2 = index1 + k < n ? index1 + k : -1;  // 10
  int index3 = index1 - k >= 0 ? index1 - k : -1;
  int seat2;
  int row2;
  int seat3;
  int row3;
  if (index2 != -1) {
    seat2 = index2 % 2 + 1;               // 1
    row2 = (index2 - seat2 + 1) / 2 + 1;  // 6
  }
  if (index3 != -1) {
    seat3 = index3 % 2 + 1;
    row3 = (index3 - seat3 + 1) / 2 + 1;
  }
  if (index2 == -1 && index3 == -1)
    cout << -1;
  else if (index2 == -1 || index3 != -1 && row1 - row3 < row2 - row1)
    cout << row3 << " " << seat3;
  else
    cout << row2 << " " << seat2;
  return 0;
}
