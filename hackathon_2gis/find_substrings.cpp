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

  int needle_length = needle.length(),
      needle_max_num_lexem = needle_length - threshold + 1,
      num_keys = needle_max_num_lexem * 2;
  string keys_needle[num_keys];
  size_t hash_needle[num_keys], pos_needle[num_keys];

  for (int i = 0; i < needle_max_num_lexem; i++) {
    string substr_needle = needle.substr(i, threshold);
    keys_needle[i] = substr_needle;
    hash_needle[i] = hash<string>{}(substr_needle);
    pos_needle[i] = i;
    cout << keys_needle[i] << "|" << hash_needle[i] << "|" << pos_needle[i]
         << endl;
  }
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
