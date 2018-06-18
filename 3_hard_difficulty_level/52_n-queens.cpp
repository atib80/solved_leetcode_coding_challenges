/*
The n-queens puzzle is the problem of placing n queens on an n×n chessboard such
that no two queens attack each other.

Given an integer n, return the number of distinct solutions to the n-queens
puzzle.

Example:

Input: 4
Output: 2
Explanation: There are two distinct solutions to the 4-queens puzzle as shown
below.
[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]
*/

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  static bool place(const int k, const vector<int>& Xx) {
    for (int i{1}; i < k; i++)
      if (Xx[i] == Xx[k] || abs(Xx[i] - Xx[k]) == abs(i - k))
        return false;

    return true;
  }

 public:
  int totalNQueens(const int n) {
    int valid_check_boards_count{};
    if (1 == n)
      return 1;
    if (n < 4)
      return 0;

    vector<int> X(n + 1, 0);

    int k{1};

    while (k > 0) {
      X[k]++;

      while (X[k] <= n && !place(k, X))
        X[k]++;

      if (X[k] <= n) {
        if (k == n)
          valid_check_boards_count++;
        else {
          k++;
          X[k] = 0;
        }
      } else
        k--;
    }

    return valid_check_boards_count;
  }
};

int main() {
  Solution s{};

  cout << "s.totalNQueens(1) -> " << s.totalNQueens(1) << '\n';
  cout << "s.totalNQueens(2) -> " << s.totalNQueens(2) << '\n';
  cout << "s.totalNQueens(3) -> " << s.totalNQueens(3) << '\n';
  cout << "s.totalNQueens(4) -> " << s.totalNQueens(4) << '\n';
  cout << "s.totalNQueens(5) -> " << s.totalNQueens(5) << '\n';
  cout << "s.totalNQueens(6) -> " << s.totalNQueens(6) << '\n';
  cout << "s.totalNQueens(7) -> " << s.totalNQueens(7) << '\n';
  cout << "s.totalNQueens(8) -> " << s.totalNQueens(8) << '\n';
  cout << "s.totalNQueens(9) -> " << s.totalNQueens(9) << '\n';
  cout << "s.totalNQueens(10) -> " << s.totalNQueens(10) << '\n';

  return 0;
}