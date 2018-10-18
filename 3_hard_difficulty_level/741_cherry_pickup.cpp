/*
741. Leetcode coding challenge: Cherry pickup

In a N x N grid representing a field of cherries, each cell is one of three
possible integers.

0 means the cell is empty, so you can pass through;
1 means the cell contains a cherry, that you can pick up and pass through;
-1 means the cell contains a thorn that blocks your way.

Your task is to collect maximum number of cherries possible by following the
rules below:

Starting at the position (0, 0) and reaching (N-1, N-1) by moving right or down
through valid path cells (cells with value 0 or 1); After reaching (N-1, N-1),
returning to (0, 0) by moving left or up through valid path cells; When passing
through a path cell containing a cherry, you pick it up and the cell becomes an
empty cell (0); If there is no valid path between (0, 0) and (N-1, N-1), then no
cherries can be collected.

Example 1:

Input: grid =
[[0, 1, -1],
 [1, 0, -1],
 [1, 1,  1]]
Output: 5
Explanation:
The player started at (0, 0) and went down, down, right right to reach (2, 2).
4 cherries were picked up during this single trip, and the matrix becomes
[[0,1,-1],[0,0,-1],[0,0,0]]. Then, the player went left, up, up, left to return
home, picking up one more cherry. The total number of cherries picked up is 5,
and this is the maximum possible.

Note:
grid is an N by N 2D array, with 1 <= N <= 50.
Each grid[i][j] is an integer in the set {-1, 0, 1}.
It is guaranteed that grid[0][0] and grid[N-1][N-1] are not -1.
*/

#include <algorithm>
#include <chrono>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  vector<vector<int>> grid_;
  vector<vector<vector<int>>> dp_;

  // max cherries picked up going from (x1, y1) to (0, 0) and (x2, y2) to (0, 0)
  int dp(const int x1, const int y1, const int x2) {
    const int y2{x1 + y1 - x2};
    if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0)
      return -1;
    if (grid_[y1][x1] < 0 || grid_[y2][x2] < 0)
      return -1;
    if (x1 == 0 && y1 == 0)
      return grid_[y1][x1];
    if (dp_[x1][y1][x2] != INT_MIN)
      return dp_[x1][y1][x2];
    int ans{max(max(dp(x1 - 1, y1, x2 - 1), dp(x1, y1 - 1, x2)),
                max(dp(x1, y1 - 1, x2 - 1), dp(x1 - 1, y1, x2)))};
    if (ans < 0)
      return dp_[x1][y1][x2] = -1;
    ans += grid_[y1][x1];
    if (x1 != x2)
      ans += grid_[y2][x2];
    return dp_[x1][y1][x2] = ans;
  }

 public:
  int cherryPickup(vector<vector<int>>& grid) {
    grid_ = move(grid);
    const int N = grid_.size();

    dp_.assign(N, vector<vector<int>>(N, vector<int>(N, INT_MIN)));
    return max(0, dp(N - 1, N - 1, N - 1));
  }

  static double start_stop_timer(const bool is_start_timer = false) {
    static chrono::high_resolution_clock::time_point start_time;
    if (is_start_timer)
      start_time = chrono::high_resolution_clock::now();

    return chrono::duration_cast<chrono::duration<double>>(
               chrono::high_resolution_clock::now() - start_time)
        .count();
  }
};

int main() {
  Solution s{};
  Solution::start_stop_timer(true);
  vector<vector<int>> input1{{0, 1, -1}, {1, 0, -1}, {1, 1, 1}};
  cout << "s.cherryPickup([[0, 1, -1],[1, 0, -1],[1, 1,  1]]) -> "
       << s.cherryPickup(input1) << '\n';  // expected output: 5

  vector<vector<int>> input2{{0, 1, 1}};
  cout << "s.cherryPickup([[0, 1, 1]]) -> " << s.cherryPickup(input2)
       << '\n';  // expected output: 2

  vector<vector<int>> input3{{0, -1, 1}};
  cout << "s.cherryPickup([[0, -1, 1]]) -> " << s.cherryPickup(input3)
       << '\n';  // expected output: 0

  vector<vector<int>> input4{{1, 1, 1, 1, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0},
                             {0, 0, 0, 1, 0, 0, 1}, {1, 0, 0, 1, 0, 0, 0},
                             {0, 0, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0},
                             {0, 0, 0, 1, 1, 1, 1}};

  cout << "s.cherryPickup([[1,1,1,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,0,0,1],"
          "[1,"
          "0,0,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,1,1,1]]) "
          "-> "
       << s.cherryPickup(input4) << '\n';  // expected output: 15

  vector<vector<int>> input5{{1, 1, -1}, {1, -1, 1}, {-1, 1, 1}};
  cout << "s.cherryPickup([[1,1,-1],[1,-1,1],[-1,1,1]]) -> "
       << s.cherryPickup(input5) << '\n';  // expected output: 0

  vector<vector<int>> input6{{1, -1, -1, -1, -1},
                             {1, 0, 1, -1, -1},
                             {0, -1, 1, 0, 1},
                             {1, 0, 1, 1, 0},
                             {-1, -1, -1, 1, 1}};
  cout << "s.cherryPickup([[1,-1,-1,-1,-1],[1,0,1,-1,-1],[0,-1,1,0,1],[1,0,1,1,"
          "0],[-1,-1,-1,1,1]]) -> "
       << s.cherryPickup(input6) << '\n';  // expected output: 10

  vector<vector<int>> input7{
      {1, 1, 1, 1, -1, -1, -1, 1, 0, 0}, {1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
      {0, 0, 1, 1, 1, 1, 0, 1, 1, 1},    {1, 1, 0, 1, 1, 1, 0, -1, 1, 1},
      {0, 0, 0, 0, 1, -1, 0, 0, 1, -1},  {1, 0, 1, 1, 1, 0, 0, -1, 1, 0},
      {1, 1, 0, 1, 0, 0, 1, 0, 1, -1},   {1, -1, 0, 1, 0, 0, 0, 1, -1, 1},
      {1, 0, -1, 0, -1, 0, 0, 1, 0, 0},  {0, 0, -1, 0, 1, 0, 1, 0, 0, 1}};
  cout << "s.cherryPickup([[1,1,1,1,-1,-1,-1,1,0,0],[1,0,0,0,1,0,0,0,1,0],[0,0,"
          "1,1,1,1,0,1,1,1],[1,1,0,1,1,1,0,-1,1,1],[0,0,0,0,1,-1,0,0,1,-1],[1,"
          "0,1,1,1,0,0,-1,1,0],[1,1,0,1,0,0,1,0,1,-1],[1,-1,0,1,0,0,0,1,-1,1],["
          "1,0,-1,0,-1,0,0,1,0,0],[0,0,-1,0,1,0,1,0,0,1]]) -> "
       << s.cherryPickup(input7) << '\n';  // expected output: 22

  vector<vector<int>> input8{
      {0, 0, 1, 0, 0, 1, 0, 1, 1, -1, 0, 0, -1, -1, 0, 1, 1, -1, 0, -1},
      {1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0},
      {1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, -1, 0, 1, 1, 0},
      {0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, -1, 1, 0, 0, 1, 0, 0, 1, 1},
      {-1, 0, -1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, -1, 1, 0, 0, 0, 1, 1},
      {0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0},
      {0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, -1, 1, 0, 1, 1, 0, 1, 1, 0},
      {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1},
      {0, 0, 0, -1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0},
      {1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, -1, 0, -1, 0, 1, 0},
      {0, 1, -1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, -1, 1, 0, 0, -1, 0},
      {0, 0, 0, 0, 1, 0, 1, 0, 0, -1, 0, 1, 0, -1, 0, 0, 1, 0, 1, 1},
      {1, -1, -1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0},
      {-1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0},
      {0, 1, -1, 1, 1, 1, 0, 0, 1, -1, 1, 1, 0, 1, 0, 1, 0, -1, 1, 0},
      {1, -1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, -1, 0, 0, 1, 0, -1},
      {-1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, -1, 0, 1, 0, 0, 1, 0},
      {0, 0, 0, -1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1},
      {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1},
      {0, 0, 0, 1, -1, 0, -1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, -1, 0}};
  cout << "s.cherryPickup([[0,0,1,0,0,1,0,1,1,-1,0,0,-1,-1,0,1,1,-1,0,-1],[1,1,"
          "1,0,1,0,0,0,0,1,1,1,1,1,1,1,0,0,1,0],[1,0,1,1,0,0,1,0,0,0,1,0,1,1,1,"
          "-1,0,1,1,0],[0,1,1,0,0,0,1,0,1,1,0,-1,1,0,0,1,0,0,1,1],[-1,0,-1,1,0,"
          "0,1,1,0,0,1,1,0,-1,1,0,0,0,1,1],[0,0,1,0,1,1,0,0,1,0,0,1,0,1,1,1,1,"
          "1,1,0],[0,0,0,1,0,1,1,0,0,1,1,-1,1,0,1,1,0,1,1,0],[0,0,0,0,0,0,1,0,"
          "0,1,0,0,1,0,0,0,1,0,1,1],[0,0,0,-1,1,0,0,1,0,0,1,1,1,1,0,0,0,1,1,0],"
          "[1,0,1,1,1,0,0,1,1,0,1,0,0,0,-1,0,-1,0,1,0],[0,1,-1,1,1,1,1,0,1,0,0,"
          "1,1,0,-1,1,0,0,-1,0],[0,0,0,0,1,0,1,0,0,-1,0,1,0,-1,0,0,1,0,1,1],[1,"
          "-1,-1,0,0,1,1,1,0,1,1,1,1,1,1,0,0,0,1,0],[-1,0,1,1,1,1,1,1,0,1,1,1,"
          "1,1,0,0,1,0,1,0],[0,1,-1,1,1,1,0,0,1,-1,1,1,0,1,0,1,0,-1,1,0],[1,-1,"
          "1,0,1,1,1,0,0,0,1,1,1,1,-1,0,0,1,0,-1],[-1,1,0,0,0,1,1,1,1,1,0,1,1,-"
          "1,0,1,0,0,1,0],[0,0,0,-1,0,1,0,0,0,0,0,0,1,0,1,1,0,0,0,1],[0,1,0,0,"
          "0,0,0,0,0,1,1,1,1,0,0,1,0,0,0,1],[0,0,0,1,-1,0,-1,1,0,1,0,0,0,0,1,0,"
          "0,1,-1,0]]) -> "
       << s.cherryPickup(input8) << '\n';  // expected output: 51

  cout << "Elapsed time: " << Solution::start_stop_timer() << " seconds\n";

  return 0;
}
