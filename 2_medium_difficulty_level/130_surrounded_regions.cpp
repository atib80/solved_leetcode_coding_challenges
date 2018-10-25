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

#include <chrono>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  vector<vector<int>> skip_open_region_coordinates_;
  size_t row_size_, col_size_;

  void replace_surrounded_Os_with_Xs(const size_t x,
                                     const size_t y,
                                     vector<vector<char>>& board) {
    board[x][y] = 'X';

    if (x > 0 && 'O' == board[x - 1][y])
      replace_surrounded_Os_with_Xs(x - 1, y, board);
    if (x < row_size_ - 1 && 'O' == board[x + 1][y])
      replace_surrounded_Os_with_Xs(x + 1, y, board);
    if (y > 0 && 'O' == board[x][y - 1])
      replace_surrounded_Os_with_Xs(x, y - 1, board);
    if (y < col_size_ - 1 && 'O' == board[x][y + 1])
      replace_surrounded_Os_with_Xs(x, y + 1, board);
  }

  void ignore_open_range_coordinates(const size_t x,
                                     const size_t y,
                                     const vector<vector<char>>& board) {
    skip_open_region_coordinates_[x][y] = 1;

    if (x > 0 && !skip_open_region_coordinates_[x - 1][y] &&
        'O' == board[x - 1][y])
      ignore_open_range_coordinates(x - 1, y, board);

    if (x < row_size_ - 1 && !skip_open_region_coordinates_[x + 1][y] &&
        'O' == board[x + 1][y])
      ignore_open_range_coordinates(x + 1, y, board);

    if (y > 0 && !skip_open_region_coordinates_[x][y - 1] &&
        'O' == board[x][y - 1])
      ignore_open_range_coordinates(x, y - 1, board);

    if (y < col_size_ - 1 && !skip_open_region_coordinates_[x][y + 1] &&
        'O' == board[x][y + 1])
      ignore_open_range_coordinates(x, y + 1, board);
  }

 public:
  void solve(vector<vector<char>>& board) {
    if (board.empty())
      return;
    row_size_ = board.size();
    col_size_ = board[0].size();

    print_board_contents(board);

    skip_open_region_coordinates_.clear();
    skip_open_region_coordinates_.resize(row_size_, vector<int>(col_size_, 0));

    for (size_t i{}, j{}; i < row_size_; i++) {
      if (skip_open_region_coordinates_[i][j])
        continue;

      if ('O' == board[i][j])
        ignore_open_range_coordinates(i, j, board);
    }

    for (size_t i{}, j{col_size_ - 1}; i < row_size_; i++) {
      if (skip_open_region_coordinates_[i][j])
        continue;

      if ('O' == board[i][j])
        ignore_open_range_coordinates(i, j, board);
    }

    for (size_t i{}, j{}; j < col_size_; j++) {
      if (skip_open_region_coordinates_[i][j])
        continue;

      if ('O' == board[i][j])
        ignore_open_range_coordinates(i, j, board);
    }

    for (size_t i{row_size_ - 1}, j{}; j < col_size_; j++) {
      if (skip_open_region_coordinates_[i][j])
        continue;

      if ('O' == board[i][j])
        ignore_open_range_coordinates(i, j, board);
    }

    for (size_t i{1}; i < row_size_ - 1; i++) {
      for (size_t j{1}; j < col_size_ - 1; j++) {
        if (skip_open_region_coordinates_[i][j])
          continue;

        if ('O' == board[i][j])
          replace_surrounded_Os_with_Xs(i, j, board);
      }
    }

    print_board_contents(board);
  }

  void print_board_contents(const vector<vector<char>>& board) const {
    if (board.empty())
      return;

    printf("\n");

    for (size_t i{}; i < col_size_; i++)
      printf("--");

    for (size_t i{}; i < row_size_; i++) {
      printf("\n|");
      for (size_t j{}; j < col_size_; j++)
        printf("%c|", board[i][j]);
    }

    printf("\n");

    for (size_t i{}; i < col_size_; i++)
      printf("--");

    printf("\n");
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

  vector<vector<char>> input1{{'X', 'X', 'X', 'X'},
                              {'X', 'O', 'O', 'X'},
                              {'X', 'X', 'O', 'X'},
                              {'O', 'O', 'X', 'X'}};

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

  vector<vector<char>> input3{
      {'X', 'O', 'X', 'O', 'X', 'O', 'O', 'O', 'X', 'O'},
      {'X', 'O', 'O', 'X', 'X', 'X', 'O', 'O', 'O', 'X'},
      {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'X'},
      {'O', 'O', 'O', 'O', 'O', 'O', 'X', 'O', 'O', 'X'},
      {'O', 'O', 'X', 'X', 'O', 'X', 'X', 'O', 'O', 'O'},
      {'X', 'O', 'O', 'X', 'X', 'X', 'O', 'X', 'X', 'O'},
      {'X', 'O', 'X', 'O', 'O', 'X', 'X', 'O', 'X', 'O'},
      {'X', 'X', 'O', 'X', 'X', 'O', 'X', 'O', 'O', 'X'},
      {'O', 'O', 'O', 'O', 'X', 'O', 'X', 'O', 'X', 'O'},
      {'X', 'X', 'O', 'X', 'X', 'X', 'X', 'O', 'O', 'O'}};

  s.solve(input3);

  vector<vector<char>> input4{
      {'X', 'O', 'X', 'O', 'X', 'O', 'O', 'O', 'X', 'O'},
      {'X', 'O', 'O', 'X', 'X', 'X', 'O', 'O', 'O', 'X'},
      {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'X'},
      {'O', 'O', 'O', 'O', 'O', 'O', 'X', 'O', 'O', 'X'},
      {'O', 'O', 'X', 'X', 'O', 'X', 'X', 'O', 'O', 'O'},
      {'X', 'O', 'O', 'X', 'X', 'X', 'X', 'X', 'X', 'O'},
      {'X', 'O', 'X', 'X', 'X', 'X', 'X', 'O', 'X', 'O'},
      {'X', 'X', 'O', 'X', 'X', 'X', 'X', 'O', 'O', 'X'},
      {'O', 'O', 'O', 'O', 'X', 'X', 'X', 'O', 'X', 'O'},
      {'X', 'X', 'O', 'X', 'X', 'X', 'X', 'O', 'O', 'O'}};

  s.solve(input4);

  cout << "Elapsed time: " << Solution::start_stop_timer() << " seconds\n";

  return 0;
}
