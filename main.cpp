#include <time.h>
#include <unistd.h>

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <random>
#include <ranges>
#include <thread>
#include <unordered_set>
#include <vector>

// simple prototype 01:00 - 02:00
// end prototype on console
// 19:40 - 20:10
// 20:40 - 00:00
// 01:30 - 04:00

using namespace std;

class gameField {
 private:
  const int HEIGHT_FIELD_ = 9;
  const int WIDTH_FIELD_ = 9;
  const int COUNT_NEXT_BALLS_ = 3;
  const int POINTS_IN_ROW_ = 5;
  unordered_map<int, char> colors_{{0, 'r'}, {1, 'g'}, {2, 'b'}, {3, 'y'}};

  unordered_set<int> field_free_;
  unordered_set<int> field_busy_;
  unordered_set<int> field_for_free_;

  vector<vector<char>> field_;
  vector<int> seq_free_points_;
  vector<int> seq_busy_points_;

  void mainFunc() {
    srand(time(NULL));
    printField();
    while (field_free_.size()) {
      addRandomPoints();
      printField();
      if (checkLines()) {
        printBingo();
        clearBingoRows();
        printField();
      }

      if (field_free_.size()) {
        swapPoints();
        printField();
        if (checkLines()) {
          printBingo();
          clearBingoRows();
          printField();
        }
      }
    }
  }

  void clearBingoRows() {
    for (const auto& cell : field_for_free_) {
      int i = getI(cell);
      int j = getJ(cell);
      field_[i][j] = ' ';
      field_busy_.erase(cell);
      field_free_.insert(cell);
    }
    field_for_free_.clear();
  }

  int setIndexFromCoord(const int& i, const int& j) {
    return i * HEIGHT_FIELD_ + j;
  }

  void checkLine(int i, int j, const int& d_i, const int& d_j,
                 int& points_in_line) {
    if (i + d_i >= 0 && i + d_i < HEIGHT_FIELD_ && j + d_j >= 0 &&
        j + d_j < WIDTH_FIELD_) {
      if (field_[i][j] != ' ' && field_[i][j] == field_[i + d_i][j + d_j]) {
        ++points_in_line;
        checkLine(i + d_i, j + d_j, d_i, d_j, points_in_line);
      }
    }
    if (points_in_line >= POINTS_IN_ROW_) {
      field_for_free_.insert(setIndexFromCoord(i, j));
    }
  }

  bool checkLines() {
    for (int i = 0; i < HEIGHT_FIELD_; ++i) {
      for (int j = 0; j < WIDTH_FIELD_; ++j) {
        int points_in_line = 1;
        checkLine(i, j, 0, 1, points_in_line);
        points_in_line = 1;
        checkLine(i, j, 1, -1, points_in_line);
        points_in_line = 1;
        checkLine(i, j, 1, 0, points_in_line);
        points_in_line = 1;
        checkLine(i, j, 1, 1, points_in_line);
      }
    }
    return field_for_free_.size();
  }

  void getRandomPoints(unordered_set<int>& field, vector<int>& seq_points,
                       int count_points) {
    seq_points.clear();
    auto gen = mt19937{random_device{}()};
    ranges::sample(begin(field), end(field), back_inserter(seq_points),
                   count_points, gen);
  }

  int getI(const int& n) const { return n / HEIGHT_FIELD_; }

  int getJ(const int& n) const { return n % WIDTH_FIELD_; }

  void printField() {
    system("clear");
    cout << "----------------field----------------\n";
    for (int i = 0; i < HEIGHT_FIELD_; ++i) {
      for (int j = 0; j < WIDTH_FIELD_; ++j) {
        if (j == 0) cout << "| ";
        cout << field_[i][j] << " | ";
      }
      cout << "\n-------------------------------------\n";
    }
    this_thread::sleep_for(chrono::milliseconds(500));
  }

  void printBingo() {
    system("clear");
    cout << "----------------BINGO----------------\n";
    for (int i = 0; i < HEIGHT_FIELD_; ++i) {
      for (int j = 0; j < WIDTH_FIELD_; ++j) {
        if (j == 0) cout << "| ";
        if (field_for_free_.contains(setIndexFromCoord(i, j)))
          cout << static_cast<char>(field_[i][j] - 'a' + 'A') << " | ";
        else
          cout << field_[i][j] << " | ";
      }
      cout << "\n-------------------------------------\n";
    }
    this_thread::sleep_for(chrono::milliseconds(1500));
  }

  void swapPoints() {
    getRandomPoints(field_busy_, seq_busy_points_, 1);
    int busy = seq_busy_points_[0];
    getRandomPoints(field_free_, seq_free_points_, 1);
    int free = seq_free_points_[0];
    swap(field_[getI(busy)][getJ(busy)], field_[getI(free)][getJ(free)]);
    field_busy_.erase(busy);
    field_busy_.insert(free);
    field_free_.erase(free);
    field_free_.insert(busy);
  }

  void addRandomPoints() {
    getRandomPoints(field_free_, seq_free_points_, COUNT_NEXT_BALLS_);
    for (int i = 0; i < seq_free_points_.size(); ++i) {
      int color = rand() % 4;
      int n = seq_free_points_[i];
      field_[getI(n)][getJ(n)] = colors_[color];
      field_free_.erase(n);
      field_busy_.insert(n);
    }
  }

 public:
  gameField() : field_(HEIGHT_FIELD_, vector<char>(WIDTH_FIELD_, ' ')) {
    for (int i = 0; i < HEIGHT_FIELD_ * WIDTH_FIELD_; ++i) {
      field_free_.insert(i);
    }
    mainFunc();
  };
};

int main() {
  gameField game;
  return 0;
}