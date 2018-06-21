/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the
diagram below).

The robot can only move either down or right at any point in time. The robot is
trying to reach the bottom-right corner of the grid (marked 'Finish' in the
diagram below).

How many possible unique paths are there?

Above is a 7 x 3 grid. How many possible unique paths are there?

Note: m and n will be at most 100.

Example 1:

Input:  m = 3, n = 2
Output: 3

Explanation:
From the top-left corner, there are a total of 3 ways to reach the bottom-right
corner:
1. Right -> Right -> Down
2. Right -> Down -> Right
3. Down -> Right -> Right

Example 2:

Input:  m = 7, n = 3
Output: 28
*/

#include <cstdint>
#include <iostream>

using namespace std;

static int sres = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

class Solution {
 public:
  static double factorial(const int number) {
    if (number < 2)
      return 1;
    double result = number;
    for (int i{number - 1}; i > 1; i--)
      result *= i;
    return result;
  }

  int64_t uniquePaths(const int m, const int n) {
    if (1 == m || 1 == n)
      return 1;
    const int x1{1}, y1{1};
    const int x2{m}, y2{n};
    const int number_of_moves_needed{x2 - x1 + y2 - y1};
    const int number_of_max_moves_right{x2 - x1};
    const int number_of_max_moves_down{y2 - y1};
    const double number_of_move_combinations{
        factorial(number_of_moves_needed) /
        (factorial(number_of_max_moves_down) *
         factorial(number_of_max_moves_right))};
    return static_cast<int64_t>(round(number_of_move_combinations));
  }
};

int main() {
  Solution s{};

  cout << "s.uniquePaths(3, 2) -> " << s.uniquePaths(3, 2)
       << '\n';  // expected output: 3
  cout << "s.uniquePaths(3, 2) -> " << s.uniquePaths(7, 3)
       << '\n';  // expected output: 28
  cout << "s.uniquePaths(2, 100) -> " << s.uniquePaths(2, 100)
       << '\n';  // expected output: 100

  return 0;
}
