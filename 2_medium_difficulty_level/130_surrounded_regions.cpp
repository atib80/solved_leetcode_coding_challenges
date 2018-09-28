/*
130. Surrounded regions (difficulty level: medium)

Given a 2D board containing 'X' and 'O' (the letter O), capture all regions
surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

Example:

X X X X
X O O X
X X O X
X O X X

After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X

Explanation:

Surrounded regions shouldn’t be on the border, which means that any 'O' on the
border of the board are not flipped to 'X'. Any 'O' that is not on the border
and it is not connected to an 'O' on the border will be flipped to 'X'. Two
cells are connected if they are adjacent cells connected horizontally or
vertically.
*/

#include <iostream>
#include <queue>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

static size_t row_size, col_size;

// namespace std {
template <>
struct hash<pair<size_t, size_t>> {
  size_t operator()(const pair<size_t, size_t>& p) const noexcept {
    return p.first * col_size + p.second;
  }
};
// }

class Solution {
  bool find_and_mark_neighboring_holes(
      const size_t x,
      const size_t y,
      const vector<vector<char>>& board,
      unordered_set<pair<size_t, size_t>>& found_region_coordinates,
      vector<vector<int>>& skip_open_region_coordinates) const {
    if (!x || !y || row_size - 1 == x || col_size - 1 == y) {
      skip_open_region_coordinates[x][y] = 1;
      return false;
    }

    found_region_coordinates.emplace(x, y);
    skip_open_region_coordinates[x][y] = 1;

    if (x > 0 && !skip_open_region_coordinates[x - 1][y] &&
        'O' == board[x - 1][y]) {
      if (!find_and_mark_neighboring_holes(x - 1, y, board,
                                           found_region_coordinates,
                                           skip_open_region_coordinates))
        return false;
    }

    if (x < row_size - 1 && !skip_open_region_coordinates[x + 1][y] &&
        'O' == board[x + 1][y]) {
      if (!find_and_mark_neighboring_holes(x + 1, y, board,
                                           found_region_coordinates,
                                           skip_open_region_coordinates))
        return false;
    }

    if (y > 0 && !skip_open_region_coordinates[x][y - 1] &&
        'O' == board[x][y - 1]) {
      if (!find_and_mark_neighboring_holes(x, y - 1, board,
                                           found_region_coordinates,
                                           skip_open_region_coordinates))
        return false;
    }

    if (y < col_size - 1 && !skip_open_region_coordinates[x][y + 1] &&
        'O' == board[x][y + 1]) {
      if (!find_and_mark_neighboring_holes(x, y + 1, board,
                                           found_region_coordinates,
                                           skip_open_region_coordinates))
        return false;
    }

    return true;
  }

  void ignore_open_range_coordinates(
      const size_t x,
      const size_t y,
      const vector<vector<char>>& board,
      vector<vector<int>>& skip_open_region_coordinates) const {
    skip_open_region_coordinates[x][y] = 1;

    if (x > 0 && !skip_open_region_coordinates[x - 1][y] &&
        'O' == board[x - 1][y])
      ignore_open_range_coordinates(x - 1, y, board,
                                    skip_open_region_coordinates);

    if (x < row_size - 1 && !skip_open_region_coordinates[x + 1][y] &&
        'O' == board[x + 1][y])
      ignore_open_range_coordinates(x + 1, y, board,
                                    skip_open_region_coordinates);

    if (y > 0 && !skip_open_region_coordinates[x][y - 1] &&
        'O' == board[x][y - 1])
      ignore_open_range_coordinates(x, y - 1, board,
                                    skip_open_region_coordinates);

    if (y < col_size - 1 && !skip_open_region_coordinates[x][y + 1] &&
        'O' == board[x][y + 1])
      ignore_open_range_coordinates(x, y + 1, board,
                                    skip_open_region_coordinates);
  }

  void print_board_contents(const vector<vector<char>>& board) const {
    if (board.empty())
      return;

    printf("\n");

    for (size_t i{}; i < col_size; i++)
      printf("--");

    for (size_t i{}; i < row_size; i++) {
      printf("\n|");

      for (size_t j{}; j < col_size; j++) {
        printf("%c|", board[i][j]);
      }
    }

    printf("\n");

    for (size_t i{}; i < col_size; i++)
      printf("--");

    printf("\n");
  }

  bool check_if_region_of_Os_is_surrounded_by_Xs(
      const unordered_set<pair<size_t, size_t>>& found_region_coordinates,
      vector<vector<int>>& skip_open_region_coordinates) const {
    const size_t last_row_index{row_size - 1};
    const size_t last_col_index{col_size - 1};

    for (const pair<size_t, size_t>& coord : found_region_coordinates) {
      if (!coord.first || !coord.second || last_row_index == coord.first ||
          last_col_index == coord.second) {
        for (const pair<size_t, size_t>& p : found_region_coordinates)
          skip_open_region_coordinates[p.first][p.second] = 1;
        return false;
      }
    }

    return true;
  }

  void convert_region_of_Os_to_Xs(
      const unordered_set<pair<size_t, size_t>>& found_region_coordinates,
      vector<vector<char>>& board) const {
    for (const pair<size_t, size_t>& coord : found_region_coordinates)
      board[coord.first][coord.second] = 'X';
  }

 public:
  void solve(vector<vector<char>>& board) const {
    row_size = board.size();
    col_size = board[0].size();
    const size_t last_row_index{row_size - 1};
    const size_t last_col_index{col_size - 1};

    print_board_contents(board);

    unordered_set<pair<size_t, size_t>> found_region_coordinates{};
    vector<vector<int>> skip_open_region_coordinates(row_size,
                                                     vector<int>(col_size, 0));

    for (size_t i{1}; i < row_size - 1; i++) {
      for (size_t j{1}; j < col_size - 1; j++) {
        if (skip_open_region_coordinates[i][j])
          continue;

        if ('O' == board[i][j]) {
          cout << "Entering cell 'O' at (" << i << ',' << j << ")\n";
          found_region_coordinates.clear();
          if (find_and_mark_neighboring_holes(i, j, board,
                                              found_region_coordinates,
                                              skip_open_region_coordinates))
            convert_region_of_Os_to_Xs(found_region_coordinates, board);
          else
            ignore_open_range_coordinates(i, j, board,
                                          skip_open_region_coordinates);
        }
      }
    }

    print_board_contents(board);
  }
};

int main() {
  Solution s{};

  vector<vector<char>> input1{{'X', 'X', 'X', 'X'},
                              {'X', 'O', 'O', 'X'},
                              {'X', 'X', 'O', 'X'},
                              {'X', 'O', 'X', 'X'}};

  s.solve(input1);

  vector<vector<char>> input2{
      {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'O',
       'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O'},
      {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'O', 'O',
       'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
      {'X', 'O', 'O', 'X', 'O', 'X', 'O', 'O', 'O', 'O',
       'X', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O', 'O'},
      {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',
       'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'X', 'O'},
      {'O', 'X', 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'X',
       'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
      {'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O',
       'O', 'X', 'O', 'O', 'O', 'O', 'O', 'X', 'X', 'O'},
      {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'O', 'O',
       'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
      {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',
       'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O', 'O'},
      {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',
       'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'O'},
      {'O', 'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O',
       'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
      {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'O',
       'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
      {'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'X',
       'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
      {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'O',
       'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
      {'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X',
       'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
      {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',
       'O', 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
      {'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O',
       'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O', 'X'},
      {'O', 'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O',
       'O', 'O', 'O', 'O', 'O', 'X', 'O', 'X', 'O', 'O'},
      {'O', 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',
       'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
      {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'X',
       'O', 'O', 'O', 'X', 'O', 'O', 'X', 'O', 'O', 'X'},
      {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',
       'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'}};

  s.solve(input2);

  return 0;
}
