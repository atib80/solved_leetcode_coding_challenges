/*
The n-queens puzzle is the problem of placing n queens on an n×n chessboard such
that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens'
placement, where 'Q' and '.' both indicate a queen and an empty space
respectively.

Example:

Input: 4
Output: [
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown
above.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

static int sr = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& data) {
  if (data.empty()) {
    os << "data is empty\n";
    return os;
  }
  os << '\n';
  for (size_t i{}; i < data.size(); i++)
    os << data[i] << '\n';

  return os;
}

ostream& operator<<(ostream& os, const vector<vector<string>>& data) {
  if (data.empty()) {
    os << "data is empty\n";
    return os;
  }
  os << '\n';
  for (size_t i{}; i < data.size(); i++) {
    for (size_t j{}; j < data[i].size(); j++)
      os << data[i][j] << '\n';
    os << "**********\n";
  }

  return os;
}

class Solution {
  vector<vector<int>> check_board_;
  // unordered_set<string> valid_check_boards_indices;
  // string index;
  size_t dim;

  static inline size_t distance(const size_t x, const size_t y) {
    return x < y ? y - x : x - y;
  }

  bool check_if_check_board_is_valid(
      const vector<pair<size_t, size_t>>& queens_positions) {
    /*
    index.clear();

    for (const pair<size_t, size_t>& qp : queens_positions) {
      size_t coord{qp.first * dim + qp.second};
      while (coord) {
        index.push_back(static_cast<char>(coord % 10 + '0'));
        coord /= 10;
      }
      index.push_back('-');
    }

    index.pop_back();
    if (valid_check_boards_indices.find(index) !=
    end(valid_check_boards_indices)) return false;
    */

    for (size_t i{}; i < dim; i++) {
      for (size_t j{}; j < dim; j++) {
        if (j == i)
          continue;

        // if (queens_positions[i].first == queens_positions[j].first ||
        // queens_positions[i].second == queens_positions[j].second) return
        // false;

        if (distance(queens_positions[i].first, queens_positions[j].first) ==
            distance(queens_positions[i].second, queens_positions[j].second))
          return false;
      }
    }

    // valid_check_boards_indices.insert(index);

    return true;
  }

  vector<string> convert_check_board_to_string() const {
    vector<string> output(dim, string(dim, '.'));
    for (size_t x{}; x < dim; x++)
      for (size_t y{}; y < dim; y++)
        if (check_board_[x][y])
          output[x][y] = 'Q';

    return output;
  }

  void construct_check_boards(vector<vector<string>>& valid_check_boards) {
    bool is_finished{};
    vector<size_t> column_indices(dim, 0);
    vector<int> column_queens(dim, 0);
    column_queens[0] = dim;  // initially there are dim queens located in the
                             // first column of check_board_

    vector<pair<size_t, size_t>> queens_positions(dim, pair<size_t, size_t>{});

    while (!is_finished) {
      for (int i = dim - 1; i >= 0; i--) {
        if (column_indices[i] == dim - 1) {
          if (!i) {
            is_finished = true;
            break;
          }
          check_board_[i][dim - 1] = 0;
          column_queens[dim - 1]--;
          column_indices[i] = 0;
          check_board_[i][0] = 1;
          queens_positions[i].first = i;
          queens_positions[i].second = 0;
          column_queens[0]++;
        } else {
          check_board_[i][column_indices[i]] = 0;
          column_queens[column_indices[i]]--;
          column_indices[i]++;
          check_board_[i][column_indices[i]] = 1;
          queens_positions[i].first = i;
          queens_positions[i].second = column_indices[i];
          column_queens[column_indices[i]]++;
          break;
        }
      }

      bool skip_current_chess_board{};

      for (size_t col{}; col < dim; col++) {
        if (column_queens[col] > 1) {
          skip_current_chess_board = true;
          break;
        }
      }

      if (skip_current_chess_board)
        continue;

      if (check_if_check_board_is_valid(queens_positions))
        valid_check_boards.emplace_back(convert_check_board_to_string());
    }
  }

 public:
  vector<vector<string>> solveNQueens(const size_t n) {
    vector<vector<string>> valid_check_boards{};
    if (n < 4)
      return valid_check_boards;

    check_board_.assign(n, vector<int>(n, 0));
    for (vector<int>& row : check_board_)
      row[0] = 1;
    dim = n;
    // index.reserve(1024);

    construct_check_boards(valid_check_boards);

    return valid_check_boards;
  }
};

int main() {
  Solution s{};

  // vector<vector<string>> output1{s.solveNQueens(2)};
  // cout << "s.solveNQueens(2) -> " << output1.size() << '\n';
  // vector<vector<string>> output2{s.solveNQueens(3)};
  // cout << "s.solveNQueens(3) -> " << output2.size() << '\n';
  // vector<vector<string>> output3{s.solveNQueens(4)};
  // cout << "s.solveNQueens(4) -> " << output3.size() << '\n';
  // vector<vector<string>> output4{s.solveNQueens(5)};
  // cout << "s.solveNQueens(5) -> " << output4.size() << '\n';
  // cout << output4 << '\n';
  // vector<vector<string>> output5{s.solveNQueens(6)};
  // cout << "s.solveNQueens(6) -> " << output5.size() << '\n';
  // vector<vector<string>> output6{s.solveNQueens(7)};
  // cout << "s.solveNQueens(7) -> " << output6.size() << '\n';
  vector<vector<string>> output7{s.solveNQueens(8)};
  cout << "s.solveNQueens(8) -> " << output7.size() << '\n';
  cout << output7 << '\n';
  // vector<vector<string>> output8{s.solveNQueens(10)};
  // cout << "s.solveNQueens(10) -> " << output8.size() << '\n';

  return 0;
}
