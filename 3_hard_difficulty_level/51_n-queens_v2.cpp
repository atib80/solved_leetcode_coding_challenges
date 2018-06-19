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
  vector<string> check_board_;

  static inline size_t distance(const size_t x, const size_t y) {
    return x < y ? y - x : x - y;
  }

  vector<vector<string>> construct_check_boards(const size_t n) {
    string check_board_indices(n, 'a');
    for (size_t i{1}; i < n; i++)
      check_board_indices[i] = static_cast<char>('a' + i);
    vector<vector<string>> valid_check_boards{};

  START:

    for (size_t i{}; i < n - 1; i++) {
      if (distance(check_board_indices[i], check_board_indices[i + 1]) == 1)
        goto NEXT_ITER;

      for (size_t j{i + 1}; j < n; j++) {
        if (distance(check_board_indices[i] - 'a',
                     check_board_indices[j] - 'a') == distance(i, j))
          goto NEXT_ITER;
      }
    }

    for (size_t col{}; col < n; col++)
      check_board_[check_board_indices[col] - 'a'][col] = 'Q';
    valid_check_boards.emplace_back(check_board_);
    for (size_t col{}; col < n; col++)
      check_board_[check_board_indices[col] - 'a'][col] = '.';

  NEXT_ITER:
    if (next_permutation(begin(check_board_indices), end(check_board_indices)))
      goto START;

    return valid_check_boards;
  }

 public:
  vector<vector<string>> solveNQueens(const size_t n) {
    if (1 == n)
      return vector<vector<string>>(1, vector<string>(1, "Q"));
    if (n < 4)
      return vector<vector<string>>{};

    check_board_.assign(n, string(n, '.'));

    return construct_check_boards(n);
  }
};

int main() {
  Solution s{};

  vector<vector<string>> output1{s.solveNQueens(2)};
  cout << "s.solveNQueens(2) -> " << output1.size() << '\n';
  vector<vector<string>> output2{s.solveNQueens(3)};
  cout << "s.solveNQueens(3) -> " << output2.size() << '\n';
  vector<vector<string>> output3{s.solveNQueens(4)};
  cout << "s.solveNQueens(4) -> " << output3.size() << '\n';
  vector<vector<string>> output4{s.solveNQueens(5)};
  cout << "s.solveNQueens(5) -> " << output4.size() << '\n';
  // cout << output4 << '\n';
  vector<vector<string>> output5{s.solveNQueens(6)};
  cout << "s.solveNQueens(6) -> " << output5.size() << '\n';
  vector<vector<string>> output6{s.solveNQueens(7)};
  cout << "s.solveNQueens(7) -> " << output6.size() << '\n';
  vector<vector<string>> output7{s.solveNQueens(8)};
  cout << "s.solveNQueens(8) -> " << output7.size() << '\n';
  // cout << output7 << '\n';
  vector<vector<string>> output8{s.solveNQueens(9)};
  cout << "s.solveNQueens(9) -> " << output8.size() << '\n';
  vector<vector<string>> output9{s.solveNQueens(10)};
  cout << "s.solveNQueens(10) -> " << output9.size() << '\n';

  return 0;
}
