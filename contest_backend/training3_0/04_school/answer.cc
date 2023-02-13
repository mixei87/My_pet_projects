// https://contest.yandex.ru/contest/45468/problems/4/
#include <fstream>
#include <iostream>
// #include <set>
// #include <vector>
using namespace std;

int main() {
  enum s { right = 1, left = 2 };

  ifstream fin("input.txt");
  size_t n, k, row, seat;
  fin >> n;
  fin >> k;
  fin >> row;
  fin >> seat;

  cout << ((row - 1) * 2 + seat) % (k + 1) << "\n";
  ofstream fout("output.txt");
  // int res = 0;
  // fout << res;

  fout.close();
  fin.close();
  return 0;
}
