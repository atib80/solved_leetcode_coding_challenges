/*
64. Leetcode coding challenge: Minimum path sum
Given a m x n grid filled with non-negative numbers, find a path from top left
to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

Example:

Input:
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]

Output: 7
Explanation: Because the path 1→3→1→1→1 minimizes the sum.
*/

#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
  void find_min_sum(vector<vector<int>>& grid,
                    const size_t last_x,
                    const size_t last_y,
                    const size_t x,
                    const size_t y,
                    int& min_sum,
                    const int current_sum) {
    if (x == last_x && y == last_y) {
      if (current_sum < min_sum)
        min_sum = current_sum;
      return;
    }

    const int saved_number{grid[x][y]};

    grid[x][y] = -1;
    if (y < last_y && -1 != grid[x][y + 1]) {
      if (current_sum + grid[x][y + 1] < min_sum)
        find_min_sum(grid, last_x, last_y, x, y + 1, min_sum,
                     current_sum + grid[x][y + 1]);
    }

    if (x < last_x && -1 != grid[x + 1][y]) {
      if (current_sum + grid[x + 1][y] < min_sum)
        find_min_sum(grid, last_x, last_y, x + 1, y, min_sum,
                     current_sum + grid[x + 1][y]);
    }

    grid[x][y] = saved_number;
  }

 public:
  Solution() = default;

  int minPathSum(vector<vector<int>>& grid) {
    if (grid.empty())
      return 0;

    const size_t m{grid.size()};

    if (1 == m)
      return accumulate(begin(grid[0]), end(grid[0]), 0);

    const size_t n{grid[0].size()};

    if (1 == n) {
      int col_sum{};
      for (const vector<int>& row : grid)
        col_sum += row[0];
      return col_sum;
    }

    const size_t last_x{m - 1};
    const size_t last_y{n - 1};
    int min_sum{numeric_limits<int>::max()};
    find_min_sum(grid, last_x, last_y, 0, 0, min_sum, grid[0][0]);
    return min_sum;
  }
};

int main() {
  Solution s{};
  vector<vector<int>> grid1{{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};

  cout << "s.minPathSum(grid1) -> " << s.minPathSum(grid1) << '\n';

  return 0;
}
