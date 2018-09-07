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
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
  vector<vector<int>> grid_;
  vector<pair<size_t, size_t>> visited_cells;
  vector<pair<size_t, size_t>> max_cherries_path;
  size_t grid_width_{};
  size_t grid_height_{};

  void pick_up_most_cherries_by_travelling_right_and_down(
      const size_t x,
      const size_t y,
      size_t& max_picked_up_cherries,
      const size_t currently_picked_up_cherries = 0) {
    visited_cells.emplace_back(x, y);

    if (x == grid_width_ - 1 && y == grid_height_ - 1) {
      if (currently_picked_up_cherries > max_picked_up_cherries) {
        max_picked_up_cherries = currently_picked_up_cherries;
        max_cherries_path = visited_cells;
        visited_cells.pop_back();
      }
      return;
    }

    if (x + 1 < grid_width_ && -1 != grid_[x + 1][y]) {
      const int cell_value{grid_[x + 1][y]};
      grid_[x + 1][y] ^= grid_[x + 1][y];
      pick_up_most_cherries_by_travelling_right_and_down(
          x + 1, y, max_picked_up_cherries,
          currently_picked_up_cherries + cell_value);
      grid_[x + 1][y] ^= cell_value;
    }

    if (y + 1 < grid_height_ && -1 != grid_[x][y + 1]) {
      const int cell_value{grid_[x][y + 1]};
      grid_[x][y + 1] ^= grid_[x][y + 1];
      pick_up_most_cherries_by_travelling_right_and_down(
          x, y + 1, max_picked_up_cherries,
          currently_picked_up_cherries + cell_value);
      grid_[x][y + 1] ^= cell_value;
    }

    visited_cells.pop_back();
  }

  void pick_up_most_cherries_by_travelling_left_and_up(
      const size_t x,
      const size_t y,
      size_t& max_picked_up_cherries,
      const size_t currently_picked_up_cherries = 0) {
    if (x == 0 && y == 0) {
      if (currently_picked_up_cherries > max_picked_up_cherries)
        max_picked_up_cherries = currently_picked_up_cherries;
      return;
    }

    if (x > 0 && -1 != grid_[x - 1][y]) {
      const int cell_value{grid_[x - 1][y]};
      grid_[x - 1][y] ^= grid_[x - 1][y];
      pick_up_most_cherries_by_travelling_left_and_up(
          x - 1, y, max_picked_up_cherries,
          currently_picked_up_cherries + cell_value);
      grid_[x - 1][y] ^= cell_value;
    }

    if (y > 0 && -1 != grid_[x][y - 1]) {
      const int cell_value{grid_[x][y - 1]};
      grid_[x][y - 1] ^= grid_[x][y - 1];
      pick_up_most_cherries_by_travelling_left_and_up(
          x, y - 1, max_picked_up_cherries,
          currently_picked_up_cherries + cell_value);
      grid_[x][y - 1] ^= cell_value;
    }
  }

 public:
  int cherryPickup(vector<vector<int>>& grid) {
    grid_ = move(grid);
    grid_height_ = grid_.size();
    grid_width_ = grid_[0].size();
    visited_cells.clear();
    visited_cells.reserve(grid_height_ + grid_width_);

    if (1 == grid_height_) {
      if (any_of(begin(grid_[0]), end(grid_[0]),
                 [](const int c) { return -1 == c; }))
        return 0;

      return count(begin(grid_[0]), end(grid_[0]), 1);
    }

    size_t max_cherries_going_right_and_down{},
        max_cherries_going_left_and_up{};
    pick_up_most_cherries_by_travelling_right_and_down(
        0, 0, max_cherries_going_right_and_down, grid_[0][0]);
    for (const auto& p : max_cherries_path)
      grid_[p.first][p.second] = 0;
    pick_up_most_cherries_by_travelling_left_and_up(
        grid_height_ - 1, grid_width_ - 1, max_cherries_going_left_and_up,
        grid_[grid_height_ - 1][grid_width_ - 1]);
    return max_cherries_going_right_and_down + max_cherries_going_left_and_up;
  }
};

int main() {
  Solution s{};
  vector<vector<int>> input1{{0, 1, -1}, {1, 0, -1}, {1, 1, 1}};
  cout << "s.cherryPickup([[0, 1, -1],[1, 0, -1],[1, 1,  1]]) -> "
       << s.cherryPickup(input1) << '\n';  // expected output: 5

  vector<vector<int>> input2{{0, 1, 1}};
  cout << "s.cherryPickup([[0, 1, 1]]) -> " << s.cherryPickup(input2)
       << '\n';  // expected output: 2

  vector<vector<int>> input3{{0, -1, 1}};
  cout << "s.cherryPickup([[0, -1, 1]]) -> " << s.cherryPickup(input3)
       << '\n';  // expected output: 0

  return 0;
}
