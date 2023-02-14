#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
  ifstream in("input.txt");
  size_t k;
  in >> k;
  string s;
  in >> s;

  // k = 3
  // abcazabcaa

  unordered_map<char, vector<int>> dict;

  for (int i = 0; i < s.size(); ++i) {
    dict[s[i]].push_back(i);
  }
  int big_max = 1;
  for (const auto& c : dict) {
    for (int i = 0; i < c.second.size(); ++i) {
      int max = 1;
      int t = k;
      for (int j = i + 1; j < c.second.size(); ++j) {
        int delta = c.second[j] - c.second[j - 1];
        if (delta == 1) {
          ++max;
        } else if (delta - 1 <= t) {
          max += delta;
          t -= delta - 1;
        } else {
          break;
        }
      }
      max += t;
      if (max > big_max) big_max = max;
    }
  }
  cout << big_max;
  in.close();
  return 0;
}
