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
  static bool place(const int k, const vector<int>& Xx) {
    //  this function will check to place k-th queen
    //  provided that k-1 queens already in the board
    for (int i{1}; i < k; i++)
      if (Xx[i] == Xx[k] || abs(Xx[i] - Xx[k]) == abs(i - k))
        return false;

    return true;
  }

 public:
  vector<vector<string>> solveNQueens(const int n) {
    vector<vector<string>> valid_check_boards{};
    if (1 == n)
      return vector<vector<string>>(1, vector<string>(1, "Q"));
    if (n < 4)
      return valid_check_boards;

    vector<int> X(n + 1, 0);

    int k{1};  //  X[1 to n] array will represent every
               //  solution. "X[i] = j" represents a queen
               //  at board[i][j] This is one dimensional
               //  array carrying two dimensional information.
    while (k > 0) {
      X[k]++;

      while (X[k] <= n && !place(k, X))
        X[k]++;

      if (X[k] <= n) {
        if (k == n) {  //  here we got a solution, now filling up the board as
                       //  needed and will insert to Solution.

          vector<string> board(n, string(n, '.'));

          for (int i{1}; i <= n; i++)
            board[i - 1][X[i] - 1] = 'Q';  // every entry in X means one Q.

          valid_check_boards.emplace_back(move(board));
        } else {
          k++;
          X[k] = 0;
        }
      } else
        k--;
    }

    return valid_check_boards;
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
