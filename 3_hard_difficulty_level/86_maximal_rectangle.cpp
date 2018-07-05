/*
86. Leetcode coding challenge: Maximal rectangle

Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle
containing only 1's and return its area.

Example:

Input:
[
  ["1","0","1","0","0"],
  ["1","0","1","1","1"],
  ["1","1","1","1","1"],
  ["1","0","0","1","0"]
]
Output: 6
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

static int sres = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

class Solution {
  vector<vector<char>> matrix_;
  size_t matrix_height;
  size_t matrix_width;

  bool find_maximal_rectangle_in_matrix(const size_t height,
                                        const size_t width) {
    for (size_t y{}; y + height <= matrix_height; y++) {
      for (size_t x{}; x + width <= matrix_width; x++) {
        bool is_rectangle_found{true};

        for (size_t i{y}; i < y + height; i++) {
          for (size_t j{x}; j < x + width; j++) {
            if (!matrix_[i][j]) {
              x = j;
              y = i;
              is_rectangle_found = false;
              break;
            }
          }

          if (!is_rectangle_found)
            break;
        }

        if (is_rectangle_found)
          return true;
      }
    }

    return false;
  }

  bool check_if_matrix_has_one_elements() {
    for (const vector<char>& row : matrix_) {
      if (any_of(begin(row), end(row),
                 [](const int value) { return 0 != value; }))
        return true;
    }

    return false;
  }

 public:
  int maximalRectangle(vector<vector<char>>& matrix) {
    if (matrix.empty())
      return 0;

    matrix_ = move(matrix);

    for (vector<char>& row : matrix_) {
      for (char& ch : row)
        ch -= '0';
    }

    if (!check_if_matrix_has_one_elements())
      return 0;

    matrix_height = matrix_.size();
    matrix_width = matrix_[0].size();
    vector<pair<size_t, size_t>> width_height_pairs{};

    for (size_t i{matrix_width}; i >= 1; i--)
      for (size_t j{matrix_height}; j >= 1; j--)
        width_height_pairs.emplace_back(make_pair(i, j));

    sort(begin(width_height_pairs), end(width_height_pairs),
         [](const pair<size_t, size_t>& lhs, const pair<size_t, size_t>& rhs) {
           return lhs.first * lhs.second > rhs.first * rhs.second;
         });

    for (size_t i{}; i < width_height_pairs.size() - 1; i++) {
      const size_t width{width_height_pairs[i].first};
      const size_t height{width_height_pairs[i].second};

      if (find_maximal_rectangle_in_matrix(width, height))
        return width * height;
    }

    return 1;
  }
};

int main() {
  Solution s{};

  vector<vector<char>> input{{'1', '0', '1', '0', '0'},
                             {'1', '0', '1', '1', '1'},
                             {'1', '1', '1', '1', '1'},
                             {'1', '0', '0', '1', '0'}};

  cout << "s.maximalRectangle({{'1','0','1','0','0'},{'1','0','1','1','1'},{'1'"
          ",'1','1','1','1'},{'1','0','0','1','0'}}) -> "
       << s.maximalRectangle(input) << '\n';

  return 0;
}
