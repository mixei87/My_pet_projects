// https://contest.yandex.ru/contest/39050/problems/
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

void add_line(vector<string>& offer_id, vector<int>& market_sku,
              vector<int>& price, const string& tmp_offer_id,
              const int& tmp_market_sku, const int& tmp_price, int left,
              int right);

int main() {
  ifstream cin("input.txt");
  int n, m;
  vector<string> offer_id;
  vector<int> market_sku;
  vector<int> price;
  cin >> n >> m;

  string line;
  getline(cin, line, ' ');
  string tmp_offer_id;
  int tmp_market_sku, tmp_price;
  for (int i = 1; getline(cin, line, ' '); i++) {
    int count_row = i % 6;
    if (count_row == 2) {
      tmp_offer_id = line.substr(1, line.find_last_of('"') - 1);
    } else if (count_row == 4) {
      tmp_market_sku = stoi(line);
    } else if (count_row == 0) {
      tmp_price = stoi(line);
      add_line(offer_id, market_sku, price, tmp_offer_id, tmp_market_sku,
               tmp_price, 0, offer_id.size());
    }
  }

  string final = "{\"offers\":[";
  for (int i = 0; i < m; i++) {
    final += "{\"market_sku\":" + to_string(market_sku[i]) +
             ",\"offer_id\":\"" + offer_id[i] +
             "\",\"price\":" + to_string(price[i]) + "}";
    if (i != m - 1) {
      final += ",";
    }
  }
  final += "]}";
  cout << final;

  return 0;
}

void add_line(vector<string>& offer_id, vector<int>& market_sku,
              vector<int>& price, const string& tmp_offer_id,
              const int& tmp_market_sku, const int& tmp_price, int left,
              int right) {
  int mid = (left + right) / 2;
  if (left == right) {
    offer_id.insert(offer_id.begin() + left, tmp_offer_id);
    market_sku.insert(market_sku.begin() + left, tmp_market_sku);
    price.insert(price.begin() + left, tmp_price);
  } else if (tmp_price > price[mid]) {
    add_line(offer_id, market_sku, price, tmp_offer_id, tmp_market_sku,
             tmp_price, mid + 1, right);
  } else if (tmp_price < price[mid]) {
    add_line(offer_id, market_sku, price, tmp_offer_id, tmp_market_sku,
             tmp_price, left, mid);
  }
}
