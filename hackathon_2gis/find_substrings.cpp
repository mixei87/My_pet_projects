#include "find_substrings.hpp"

int main() {
  string haystack, needle;
  CreateStringFromFile(&haystack, "haystack.txt");
  CreateStringFromFile(&needle, "needle.txt");
  // cout << "Input threshold:\n";
  int threshold = 3;  // test value
  // cin >> threshold;
  cout << haystack << endl << needle << endl << threshold << endl;
  // cout << hash<string>{}(haystack);
  return 0;
}

void CreateStringFromFile(string *str_out, string filename) {
  stringstream buff_string;
  ifstream file(filename, ios_base ::in);
  if (file.is_open()) {
    buff_string << file.rdbuf();
    *str_out = buff_string.str();
    file.close();
    return;
  }
  exit(1);
}
