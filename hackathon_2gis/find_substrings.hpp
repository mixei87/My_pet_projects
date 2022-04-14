#ifndef _FIND_SUBSTRINGS_
#define _FIND_SUBSTRINGS_
#include <fstream>
// #include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
using namespace std;
void CheckInputData(size_t haystack_length, int needle_length, int threshold);
void CreateStringFromFile(string *str, string filename);
void CreateHashTableNeedle(
    string substr_needle, int num_keys,
    vector<tuple<bool, size_t, string, size_t>> hash_needle, int pos_str);
int FindSubstringInHashTable(
    string substr_haystack, int num_keys,
    vector<tuple<bool, size_t, string, size_t>> hash_needle);
#endif