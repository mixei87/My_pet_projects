// https://contest.yandex.ru/contest/45468/problems/3/
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
  ifstream fin("input.txt");
  size_t n;
  fin >> n;
  set<size_t> di;
  for (size_t i = 0; i < n; ++i) {
    size_t x;
    fin >> x;
    di.insert(x);
  }
  vector<size_t> vec;
  for (const size_t& d : di) {
    vec.push_back(d);
  }

  fin >> n;
  ofstream fout("output.txt");
  for (size_t i = 0; i < n; ++i) {
    size_t res = 0;
    if (!vec.empty()) {
      size_t x;
      fin >> x;
      auto it = lower_bound(vec.begin(), vec.end(), x);
      if (it == vec.end()) {
        --it;
      }
      while (it != vec.end()) {
        if (*it < x) {
          res = it - vec.begin() + 1;
          break;
        }
        if (it == vec.begin()) break;
        --it;
      }
    }
    fout << res << "\n";
  }
  fout.close();
  fin.close();
  return 0;
}
