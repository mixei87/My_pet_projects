#include "find_substrings.hpp"

int main() {
  string haystack, needle;
  CreateStringFromFile(&haystack, "haystack.txt");
  CreateStringFromFile(&needle, "needle.txt");
  // cout << "Input threshold:\n";
  int threshold = 1000;  // test value
  size_t haystack_length = haystack.length();
  size_t haystack_max_num_lexem = haystack_length - threshold + 1;
  // cin >> threshold;
  // cout << "haystack:" << haystack << endl;
  //      << "needle:" << needle << endl
  //      << "threshold:" << threshold << endl;

  int needle_length = needle.length();
  if (needle_length - threshold + 1 <= 0) exit(0);
  int needle_max_num_lexem = needle_length - threshold + 1,
      num_keys = needle_max_num_lexem * 2;
  // cout << "num_keys: " << num_keys << endl;
  tuple<bool, size_t, string, size_t> hash_needle[num_keys];

  for (int i = 0; i < num_keys; i++) {
    get<0>(hash_needle[i]) = false;
  }
  for (int pos_str = 0; pos_str < needle_max_num_lexem; pos_str++) {
    string substr_needle = needle.substr(pos_str, threshold);
    // string substr_needle(needle, min(needle_length, threshold));
    CreateHashTableNeedle(substr_needle, num_keys, hash_needle, pos_str);
  }

  for (size_t pos_str = 0; pos_str < haystack_max_num_lexem; pos_str++) {
    // ! NEED CHECK OUT OF RANGE: substr(pos_str, threshold)
    if (pos_str + threshold < haystack_length) {
      string substr_haystack = haystack.substr(pos_str, threshold);
      int pos_needle =
          FindSubstringInHashTable(substr_haystack, num_keys, hash_needle);
      if (pos_needle != -1) {
        size_t start_haystack = pos_str, start_needle = pos_needle,
               len_seq = size_t(threshold);
        pos_str += threshold - 1;
        pos_needle += threshold - 1;

        for (;
             (++pos_str < haystack_length) && (++pos_needle < needle_length) &&
             (haystack[pos_str] == needle[pos_needle]);
             len_seq++)
          ;
        pos_str--;
        cout << "sequence of length = " << len_seq
             << " found at haystack offset " << start_haystack
             << ", needle offset " << start_needle << endl;
      }
    }
  }
  return 0;
}

int FindSubstringInHashTable(string substr_haystack, int num_keys,
                             tuple<bool, size_t, string, size_t> *hash_needle) {
  size_t hash_code = hash<string>{}(substr_haystack);
  int pos_hash_table = hash_code % num_keys;
  while (get<0>(hash_needle[pos_hash_table]) == true) {
    if (get<1>(hash_needle[pos_hash_table]) == hash_code &&
        get<2>(hash_needle[pos_hash_table]) == substr_haystack)
      return get<3>(hash_needle[pos_hash_table]);
    pos_hash_table = (pos_hash_table + 1) % num_keys;
  }
  return -1;
}

void CreateHashTableNeedle(string substr_needle, int num_keys,
                           tuple<bool, size_t, string, size_t> *hash_needle,
                           int pos_str) {
  size_t hash_code = hash<string>{}(substr_needle);
  int pos_hash_table = hash_code % num_keys;
  while (get<0>(hash_needle[pos_hash_table]) == true) {
    if (get<1>(hash_needle[pos_hash_table]) == hash_code &&
        get<2>(hash_needle[pos_hash_table]) == substr_needle)
      break;
    pos_hash_table = (pos_hash_table + 1) % num_keys;
  }
  hash_needle[pos_hash_table] =
      make_tuple(true, hash_code, substr_needle, pos_str);

  // cout << pos_hash_table << "|" << get<1>(hash_needle[pos_hash_table]) << "|"
  //      << get<2>(hash_needle[pos_hash_table]) << "|"
  //      << get<3>(hash_needle[pos_hash_table]) << endl;
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
