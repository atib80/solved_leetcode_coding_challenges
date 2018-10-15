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

[1, 1, 1, 1, 0, 0, 0]
[0, 0, 0, 1, 0, 0, 0]
[0, 0, 0, 1, 0, 0, 1]
[1, 0, 0, 1, 0, 0, 0]
[0, 0, 0, 1, 0, 0, 0]
[0, 0, 0, 1, 0, 0, 0]
[0, 0, 0, 1, 1, 1, 1]

Note:
grid is an N by N 2D array, with 1 <= N <= 50.
Each grid[i][j] is an integer in the set {-1, 0, 1}.
It is guaranteed that grid[0][0] and grid[N-1][N-1] are not -1.
*/

#include <algorithm>
#include <chrono>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

static size_t grid_width;

namespace std {
template <>
struct hash<pair<size_t, size_t>> {
  size_t operator()(const pair<size_t, size_t>& p) const noexcept {
    return p.first * grid_width + p.second;
  }
};
}  // namespace std

struct cell {
  size_t x;
  size_t y;
  size_t cherry_count;

  cell(const size_t x_coord, const size_t y_coord, const size_t cherries)
      : x{x_coord}, y{y_coord}, cherry_count{cherries} {}
};

class Solution {
  vector<vector<int>> grid_;
  unordered_map<pair<size_t, size_t>, size_t>
      registered_min_cherries_for_nodes_right_down_;
  unordered_map<pair<size_t, size_t>, size_t>
      registered_min_cherries_for_nodes_left_up_;
  vector<cell> currently_visited_cells_by_going_down_and_right_;
  vector<cell> currently_visited_cells_by_going_up_and_left_;
  size_t grid_width_{};
  size_t grid_height_{};
  size_t max_cherry_count_{};

  void update_currently_picked_up_cherries_for_visited_cells() {
    unordered_map<pair<size_t, size_t>, size_t>
        number_of_picked_up_cherries_at_nodes_going_down_and_right{};
    unordered_map<pair<size_t, size_t>, size_t>
        number_of_picked_up_cherries_at_nodes_going_up_and_left{};

    for (const cell& c : currently_visited_cells_by_going_down_and_right_)
      number_of_picked_up_cherries_at_nodes_going_down_and_right[make_pair(
          c.x, c.y)] = c.cherry_count;

    registered_min_cherries_for_nodes_right_down_.swap(
        number_of_picked_up_cherries_at_nodes_going_down_and_right);

    for (const cell& c : currently_visited_cells_by_going_up_and_left_)
      number_of_picked_up_cherries_at_nodes_going_up_and_left[make_pair(
          c.x, c.y)] = c.cherry_count;

    registered_min_cherries_for_nodes_left_up_.swap(
        number_of_picked_up_cherries_at_nodes_going_up_and_left);
  }

  bool pick_up_most_cherries_by_traveling_right_and_down(
      const size_t x,
      const size_t y,
      size_t& max_cherries_picked_up,
      const size_t currently_picked_up_cherries) {
    if (currently_picked_up_cherries + 2 * grid_height_ - 2 - x +
            2 * grid_width_ - 2 - y <=
        max_cherries_picked_up)
      return false;

    if (x == grid_width_ - 1 && y == grid_height_ - 1)
      return pick_up_most_cherries_by_traveling_left_and_up(
          grid_height_ - 1, grid_width_ - 1, max_cherries_picked_up,
          currently_picked_up_cherries);

    if (x < grid_height_ - 1 && -1 != grid_[x + 1][y]) {
      const int cell_value{grid_[x + 1][y]};
      const size_t current_cell_cherry_count{currently_picked_up_cherries +
                                             cell_value};
      const auto found_iter{registered_min_cherries_for_nodes_right_down_.find(
          make_pair(x + 1, y))};
      if (found_iter != end(registered_min_cherries_for_nodes_right_down_) &&
          found_iter->second >= current_cell_cherry_count)
        return false;
      currently_visited_cells_by_going_down_and_right_.emplace_back(
          x + 1, y, current_cell_cherry_count);
      grid_[x + 1][y] = 0;
      if (pick_up_most_cherries_by_traveling_right_and_down(
              x + 1, y, max_cherries_picked_up,
              currently_picked_up_cherries + cell_value))
        return true;
      currently_visited_cells_by_going_down_and_right_.pop_back();
      grid_[x + 1][y] = cell_value;
    }

    if (y < grid_width_ - 1 && -1 != grid_[x][y + 1]) {
      const int cell_value{grid_[x][y + 1]};
      const size_t current_cell_cherry_count{currently_picked_up_cherries +
                                             cell_value};
      const auto found_iter{registered_min_cherries_for_nodes_right_down_.find(
          make_pair(x, y + 1))};
      if (found_iter != end(registered_min_cherries_for_nodes_right_down_) &&
          found_iter->second >= current_cell_cherry_count)
        return false;
      currently_visited_cells_by_going_down_and_right_.emplace_back(
          x, y + 1, current_cell_cherry_count);
      grid_[x][y + 1] = 0;
      if (pick_up_most_cherries_by_traveling_right_and_down(
              x, y + 1, max_cherries_picked_up,
              currently_picked_up_cherries + cell_value))
        return true;
      currently_visited_cells_by_going_down_and_right_.pop_back();
      grid_[x][y + 1] = cell_value;
    }

    return false;
  }

  bool pick_up_most_cherries_by_traveling_left_and_up(
      const size_t x,
      const size_t y,
      size_t& max_cherries_picked_up,
      const size_t currently_picked_up_cherries) {
    if (currently_picked_up_cherries + x + y <= max_cherries_picked_up)
      return false;

    if (x == 0 && y == 0) {
      if (currently_picked_up_cherries > max_cherries_picked_up) {
        max_cherries_picked_up = currently_picked_up_cherries;
        if (currently_picked_up_cherries == max_cherry_count_)
          return true;
        update_currently_picked_up_cherries_for_visited_cells();
      }

      return false;
    }

    if (x > 0 && -1 != grid_[x - 1][y]) {
      const int cell_value{grid_[x - 1][y]};
      const size_t current_cell_cherry_count{currently_picked_up_cherries +
                                             cell_value};
      const auto found_iter{
          registered_min_cherries_for_nodes_left_up_.find(make_pair(x - 1, y))};
      if (found_iter != end(registered_min_cherries_for_nodes_left_up_) &&
          found_iter->second >= current_cell_cherry_count)
        return false;
      currently_visited_cells_by_going_up_and_left_.emplace_back(
          x - 1, y, current_cell_cherry_count);
      grid_[x - 1][y] = 0;
      if (pick_up_most_cherries_by_traveling_left_and_up(
              x - 1, y, max_cherries_picked_up,
              currently_picked_up_cherries + cell_value))
        return true;
      currently_visited_cells_by_going_up_and_left_.pop_back();
      grid_[x - 1][y] = cell_value;
    }

    if (y > 0 && -1 != grid_[x][y - 1]) {
      const int cell_value{grid_[x][y - 1]};
      const size_t current_cell_cherry_count{currently_picked_up_cherries +
                                             cell_value};
      const auto found_iter{
          registered_min_cherries_for_nodes_left_up_.find(make_pair(x, y - 1))};
      if (found_iter != end(registered_min_cherries_for_nodes_left_up_) &&
          found_iter->second >= current_cell_cherry_count)
        return false;
      currently_visited_cells_by_going_up_and_left_.emplace_back(
          x, y - 1, current_cell_cherry_count);
      grid_[x][y - 1] = 0;
      if (pick_up_most_cherries_by_traveling_left_and_up(
              x, y - 1, max_cherries_picked_up,
              currently_picked_up_cherries + cell_value))
        return true;
      currently_visited_cells_by_going_up_and_left_.pop_back();
      grid_[x][y - 1] = cell_value;
    }

    return false;
  }

 public:
  int cherryPickup(vector<vector<int>>& grid) {
    grid_ = move(grid);
    grid_height_ = grid_.size();
    grid_width = grid_width_ = grid_[0].size();

    if (1 == grid_height_) {
      if (any_of(begin(grid_[0]), end(grid_[0]),
                 [](const int c) { return -1 == c; }))
        return 0;

      return count(begin(grid_[0]), end(grid_[0]), 1);
    }

    registered_min_cherries_for_nodes_right_down_.clear();
    registered_min_cherries_for_nodes_left_up_.clear();
    max_cherry_count_ = 0;

    for (const auto& row : grid_)
      max_cherry_count_ += count(begin(row), end(row), 1);

    currently_visited_cells_by_going_down_and_right_.clear();
    currently_visited_cells_by_going_down_and_right_.reserve(grid_width_ +
                                                             grid_height_);

    currently_visited_cells_by_going_up_and_left_.clear();
    currently_visited_cells_by_going_up_and_left_.reserve(grid_width_ +
                                                          grid_height_);

    size_t max_cherries_picked_up{};
    const int start_cell_value{grid_[0][0]};
    grid_[0][0] = 0;

    if (pick_up_most_cherries_by_traveling_right_and_down(
            0, 0, max_cherries_picked_up, start_cell_value))
      cout << "Picked up max. available cherries (" << max_cherries_picked_up
           << ")\n";
    return max_cherries_picked_up;
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

  // vector<vector<int>> input8{
  //     {0, 0, 1, 0, 0, 1, 0, 1, 1, -1, 0, 0, -1, -1, 0, 1, 1, -1, 0, -1},
  //     {1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0},
  //     {1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, -1, 0, 1, 1, 0},
  //     {0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, -1, 1, 0, 0, 1, 0, 0, 1, 1},
  //     {-1, 0, -1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, -1, 1, 0, 0, 0, 1, 1},
  //     {0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0},
  //     {0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, -1, 1, 0, 1, 1, 0, 1, 1, 0},
  //     {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1},
  //     {0, 0, 0, -1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0},
  //     {1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, -1, 0, -1, 0, 1, 0},
  //     {0, 1, -1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, -1, 1, 0, 0, -1, 0},
  //     {0, 0, 0, 0, 1, 0, 1, 0, 0, -1, 0, 1, 0, -1, 0, 0, 1, 0, 1, 1},
  //     {1, -1, -1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0},
  //     {-1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0},
  //     {0, 1, -1, 1, 1, 1, 0, 0, 1, -1, 1, 1, 0, 1, 0, 1, 0, -1, 1, 0},
  //     {1, -1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, -1, 0, 0, 1, 0, -1},
  //     {-1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, -1, 0, 1, 0, 0, 1, 0},
  //     {0, 0, 0, -1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1},
  //     {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1},
  //     {0, 0, 0, 1, -1, 0, -1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, -1, 0}};
  // cout <<
  // "s.cherryPickup([[0,0,1,0,0,1,0,1,1,-1,0,0,-1,-1,0,1,1,-1,0,-1],[1,1,"
  //         "1,0,1,0,0,0,0,1,1,1,1,1,1,1,0,0,1,0],[1,0,1,1,0,0,1,0,0,0,1,0,1,1,1,"
  //         "-1,0,1,1,0],[0,1,1,0,0,0,1,0,1,1,0,-1,1,0,0,1,0,0,1,1],[-1,0,-1,1,0,"
  //         "0,1,1,0,0,1,1,0,-1,1,0,0,0,1,1],[0,0,1,0,1,1,0,0,1,0,0,1,0,1,1,1,1,"
  //         "1,1,0],[0,0,0,1,0,1,1,0,0,1,1,-1,1,0,1,1,0,1,1,0],[0,0,0,0,0,0,1,0,"
  //         "0,1,0,0,1,0,0,0,1,0,1,1],[0,0,0,-1,1,0,0,1,0,0,1,1,1,1,0,0,0,1,1,0],"
  //         "[1,0,1,1,1,0,0,1,1,0,1,0,0,0,-1,0,-1,0,1,0],[0,1,-1,1,1,1,1,0,1,0,0,"
  //         "1,1,0,-1,1,0,0,-1,0],[0,0,0,0,1,0,1,0,0,-1,0,1,0,-1,0,0,1,0,1,1],[1,"
  //         "-1,-1,0,0,1,1,1,0,1,1,1,1,1,1,0,0,0,1,0],[-1,0,1,1,1,1,1,1,0,1,1,1,"
  //         "1,1,0,0,1,0,1,0],[0,1,-1,1,1,1,0,0,1,-1,1,1,0,1,0,1,0,-1,1,0],[1,-1,"
  //         "1,0,1,1,1,0,0,0,1,1,1,1,-1,0,0,1,0,-1],[-1,1,0,0,0,1,1,1,1,1,0,1,1,-"
  //         "1,0,1,0,0,1,0],[0,0,0,-1,0,1,0,0,0,0,0,0,1,0,1,1,0,0,0,1],[0,1,0,0,"
  //         "0,0,0,0,0,1,1,1,1,0,0,1,0,0,0,1],[0,0,0,1,-1,0,-1,1,0,1,0,0,0,0,1,0,"
  //         "0,1,-1,0]]) -> "
  //      << s.cherryPickup(input8) << '\n';  // expected output: 22

  cout << "Elapsed time: " << Solution::start_stop_timer() << " seconds\n";

  return 0;
}
