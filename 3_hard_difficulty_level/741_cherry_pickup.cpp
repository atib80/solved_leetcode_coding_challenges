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
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
  vector<vector<int>> grid_;
  size_t grid_width_{};
  size_t grid_height_{};
  size_t max_cherry_count_{};

  static inline int distance(const int x1,
                             const int y1,
                             const int x2,
                             const int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
  }

  bool is_there_a_cherry_in_given_column_going_downwards(
      const size_t x,
      const size_t y,
      size_t& found_closest_cherry_x) const {
    for (size_t i{x}; i < grid_height_; i++) {
      if (1 == grid_[i][y]) {
        found_closest_cherry_x = i;
        return true;
      }

      if (-1 == grid_[i][y])
        return false;
    }
    return false;
  }

  bool is_there_a_cherry_in_given_column_going_upwards(
      const size_t x,
      const size_t y,
      size_t& found_closest_cherry_x) const {
    for (size_t i{}; i <= x; i++) {
      if (1 == grid_[i][y]) {
        found_closest_cherry_x = i;
        return true;
      }

      if (-1 == grid_[i][y])
        return false;
    }
    return false;
  }

  bool is_there_a_cherry_in_given_row_going_right(
      const size_t x,
      const size_t y,
      size_t& found_closest_cherry_y) const {
    for (size_t j{y}; j < grid_width_; j++) {
      if (1 == grid_[x][j]) {
        found_closest_cherry_y = j;
        return true;
      }

      if (-1 == grid_[x][j])
        return false;
    }
    return false;
  }

  bool is_there_a_cherry_in_given_row_going_left(
      const size_t x,
      const size_t y,
      size_t& found_closest_cherry_y) const {
    for (size_t j{}; j <= y; j++) {
      if (1 == grid_[x][j]) {
        found_closest_cherry_y = j;
        return true;
      }

      if (-1 == grid_[x][j])
        return false;
    }
    return false;
  }

  void pick_up_most_cherries_by_travelling_right_and_down(
      const size_t x,
      const size_t y,
      size_t& max_cherries_picked_up,
      const size_t currently_picked_up_cherries = 0) {
    if (x == grid_width_ - 1 && y == grid_height_ - 1) {
      pick_up_most_cherries_by_travelling_left_and_up(
          grid_height_ - 1, grid_width_ - 1, max_cherries_picked_up,
          currently_picked_up_cherries);
      return;
    }

    size_t ii{};

    if (is_there_a_cherry_in_given_column_going_downwards(x, y, ii)) {
      grid_[ii][y] = 0;
      if (ii < grid_height_ - 1)
        pick_up_most_cherries_by_travelling_right_and_down(
            ii + 1, y, max_cherries_picked_up,
            currently_picked_up_cherries + 1);
      if (y < grid_width_ - 1)
        pick_up_most_cherries_by_travelling_right_and_down(
            ii, y + 1, max_cherries_picked_up,
            currently_picked_up_cherries + 1);
      grid_[ii][y] = 1;
    } else if (y < grid_width_ - 1 && -1 != grid_[x][y + 1])
      pick_up_most_cherries_by_travelling_right_and_down(
          x, y + 1, max_cherries_picked_up, currently_picked_up_cherries);

    size_t jj{};

    if (is_there_a_cherry_in_given_row_going_right(x, y, jj)) {
      grid_[x][jj] = 0;
      if (jj < grid_width_ - 1)
        pick_up_most_cherries_by_travelling_right_and_down(
            x, jj + 1, max_cherries_picked_up,
            currently_picked_up_cherries + 1);
      if (x < grid_height_ - 1)
        pick_up_most_cherries_by_travelling_right_and_down(
            x + 1, jj, max_cherries_picked_up,
            currently_picked_up_cherries + 1);
      grid_[x][jj] = 1;
    } else if (x < grid_height_ - 1 && -1 != grid_[x + 1][y])
      pick_up_most_cherries_by_travelling_right_and_down(
          x + 1, y, max_cherries_picked_up, currently_picked_up_cherries);
  }

  void pick_up_most_cherries_by_travelling_left_and_up(
      const size_t x,
      const size_t y,
      size_t& max_cherries_picked_up,
      const size_t currently_picked_up_cherries) {
    if (currently_picked_up_cherries + distance(0, 0, x, y) <=
        max_cherries_picked_up)
      return;

    if (x == 0 && y == 0) {
      if (currently_picked_up_cherries > max_cherries_picked_up)
        max_cherries_picked_up = currently_picked_up_cherries;
      return;
    }

    size_t ii{};

    if (is_there_a_cherry_in_given_column_going_upwards(x, y, ii)) {
      grid_[ii][y] = 0;
      if (ii > 0)
        pick_up_most_cherries_by_travelling_left_and_up(
            ii - 1, y, max_cherries_picked_up,
            currently_picked_up_cherries + 1);
      if (y > 0)
        pick_up_most_cherries_by_travelling_left_and_up(
            ii, y - 1, max_cherries_picked_up,
            currently_picked_up_cherries + 1);
      grid_[ii][y] = 1;
    } else if (y > 0 && -1 != grid_[x][y - 1])
      pick_up_most_cherries_by_travelling_left_and_up(
          x, y - 1, max_cherries_picked_up, currently_picked_up_cherries);

    size_t jj{};

    if (is_there_a_cherry_in_given_row_going_left(x, y, jj)) {
      grid_[x][jj] = 0;
      if (jj > 0)
        pick_up_most_cherries_by_travelling_left_and_up(
            x, jj - 1, max_cherries_picked_up,
            currently_picked_up_cherries + 1);
      if (x > 0)
        pick_up_most_cherries_by_travelling_left_and_up(
            x - 1, jj, max_cherries_picked_up,
            currently_picked_up_cherries + 1);
      grid_[x][jj] = 1;
    } else if (x > 0 && -1 != grid_[x - 1][y])
      pick_up_most_cherries_by_travelling_left_and_up(
          x - 1, y, max_cherries_picked_up, currently_picked_up_cherries);
  }

 public:
  int cherryPickup(vector<vector<int>>& grid) {
    grid_ = move(grid);
    grid_height_ = grid_.size();
    grid_width_ = grid_[0].size();

    max_cherry_count_ = 0;
    for (size_t x{}; x < grid_height_; x++) {
      for (size_t y{}; y < grid_width_; y++) {
        if (1 == grid_[x][y])
          max_cherry_count_++;
      }
    }

    if (1 == grid_height_) {
      if (any_of(begin(grid_[0]), end(grid_[0]),
                 [](const int c) { return -1 == c; }))
        return 0;

      return count(begin(grid_[0]), end(grid_[0]), 1);
    }

    size_t max_cherries_picked_up{};
    const int start_cherry_count{grid_[0][0]};
    grid_[0][0] = 0;
    pick_up_most_cherries_by_travelling_right_and_down(
        0, 0, max_cherries_picked_up, start_cherry_count);
    return max_cherries_picked_up;
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

  vector<vector<int>> input4{{1, 1, 1, 1, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0},
                             {0, 0, 0, 1, 0, 0, 1}, {1, 0, 0, 1, 0, 0, 0},
                             {0, 0, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0},
                             {0, 0, 0, 1, 1, 1, 1}};
  cout << "s.cherryPickup([[1,1,1,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,0,0,1],"
          "[1,"
          "0,0,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,1,1,1]]) "
          "-> "
       << s.cherryPickup(input4) << '\n';  // expected output: 15

  return 0;
}
