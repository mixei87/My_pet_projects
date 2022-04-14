#include "find_substrings.hpp"

// В решении данной задачи руководствуюсь следующим:
// Беру самое левое вхождение подстроки needle, минимально удовлетворяющее
// условие вхождения в строку haystack.
//
int main() {
  string haystack, needle;
  // Данные строк хранятся в соответсвующих файлах
  CreateStringFromFile(&haystack, "haystack.txt");
  CreateStringFromFile(&needle, "needle.txt");
  // cout << "Input threshold:\n";
  int threshold = 3;  // test value
  // cin >> threshold;
  size_t haystack_length = haystack.length();
  int needle_length = needle.length();
  CheckInputData(haystack_length, needle_length, threshold);
  size_t haystack_max_num_lexem = haystack_length - threshold + 1;
  int needle_max_num_lexem = needle_length - threshold + 1,
      num_keys = needle_max_num_lexem * 2;

  vector<tuple<bool, size_t, string, size_t>> hash_needle(num_keys);
  for (int i = 0; i < num_keys; i++) {
    get<0>(hash_needle[i]) = false;
  }
  // cout << needle_max_num_lexem << endl;
  for (int pos_str = 0; pos_str < 5 /* needle_max_num_lexem*/; pos_str++) {
    // cout << needle.size() << endl;
    string substr_needle = needle.substr(pos_str, threshold);
    // string substr_needle;
    // copy(needle.begin() + pos_str, needle.begin() + pos_str + threshold,
    //      substr_needle.begin());
    // cout << substr_needle << endl;
    // string substr_needle(needle, min(needle_length, threshold));
    CreateHashTableNeedle(substr_needle, num_keys, hash_needle, pos_str);
  }

  for (size_t pos_str = 0; pos_str < haystack_max_num_lexem; pos_str++) {
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

void CheckInputData(size_t haystack_length, int needle_length, int threshold) {
  if ((threshold >= needle_length + 1) || (threshold >= haystack_length + 1)) {
    cout << "threshold is more length input string(s)";
    exit(1);
  }
}

int FindSubstringInHashTable(
    string substr_haystack, int num_keys,
    vector<tuple<bool, size_t, string, size_t>> hash_needle) {
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

void CreateHashTableNeedle(
    string substr_needle, int num_keys,
    vector<tuple<bool, size_t, string, size_t>> hash_needle, int pos_str) {
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
  cout << "No input file(s)\n";
  exit(1);
}
