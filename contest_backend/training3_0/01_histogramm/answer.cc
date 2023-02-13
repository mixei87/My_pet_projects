// https://contest.yandex.ru/contest/45468/problems
#include <fstream>
#include <iostream>
#include <map>
using namespace std;

int main() {
  ifstream fin("input.txt");
  char x;
  map<char, int> t;
  int max = 1;
  while (fin >> x) {
    ++t[x];
    if (t[x] > max) max = t[x];
  }
  int cur_max = max;
  for (int i = 0; i < max; ++i, --cur_max) {
    for (const auto& a : t) {
      if (a.second >= cur_max)
        cout << "#";
      else
        cout << " ";
    }
    cout << "\n";
  }
  for (const auto& a : t) {
    cout << a.first;
  }

  fin.close();
  return 0;
}
