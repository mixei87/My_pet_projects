#include <functional>
#include <iostream>
#include <string>

int main() {
  using std::cin;
  using std::cout;
  using std::endl;
  using std::hash;
  using std::string;
  string haystack;
  cout << "Input haystack:\n";
  getline(cin, haystack);
  // cout << "Input needle:\n";
  // string needle;
  // getline(cin, needle);
  // cout << "Input threshold:\n";
  // int threshold;
  // cin >> threshold;
  cout << "Hello, Hackathon!\n"
       << haystack << endl /*
        << needle << endl
        << threshold << endl*/
      ;
  cout << hash<string>{}(haystack);
  return 0;
}
