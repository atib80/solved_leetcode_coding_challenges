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
#include <set>
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

  int find_maximal_rectangle_in_matrix() {
    multiset<pair<size_t, int>> intersections{};

    for (const vector<char>& row : matrix_) {
      size_t start{string::npos};
      for (size_t y{}; y < matrix_width; y++) {
        if (string::npos != start && '0' == row[y] && y - start > 1) {
          intersections.insert(make_pair(start, 1));
          intersections.insert(make_pair(y, -1));
          start = string::npos;
        } else if (string::npos == start && '1' == row[y]) {
          start = y;
        }
      }

      if (string::npos != start && matrix_width - start > 1) {
        intersections.insert(make_pair(start, 1));
        intersections.insert(make_pair(matrix_width, -1));
      }
    }

    int maximal_rectangle{1};

    auto current_iter = begin(intersections);
    size_t start{current_iter->first};
    int current_rect{current_iter->second};
    ++current_iter;

    while (current_iter != end(intersections)) {
      if (-1 == current_iter->second && string::npos != start) {
        const int product{current_rect * static_cast<int>(current_iter->first - start)};
        if (product > maximal_rectangle)
          maximal_rectangle = product;
      } else if (string::npos == start && 1 == current_iter->second)
        start = current_iter->first;

      current_rect += current_iter->second;
      if (0 == current_rect)
        start = string::npos;
      ++current_iter;
    }

    return maximal_rectangle;
  }

  bool check_if_matrix_has_one_elements() {
    for (const vector<char>& row : matrix_) {
      if (any_of(begin(row), end(row),
                 [](const int value) { return '0' != value; }))
        return true;
    }

    return false;
  }

 public:
  int maximalRectangle(vector<vector<char>>& matrix) {
    if (matrix.empty())
      return 0;

    matrix_ = move(matrix);
    matrix_height = matrix_.size();
    matrix_width = matrix_[0].size();

    if (!check_if_matrix_has_one_elements())
      return 0;

    return find_maximal_rectangle_in_matrix();
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
       << s.maximalRectangle(input) << '\n';  // expected output: 6

  input.assign({{'1', '0', '1', '1', '1'},
                {'0', '1', '0', '1', '0'},
                {'1', '1', '0', '1', '1'},
                {'1', '1', '0', '1', '1'},
                {'0', '1', '1', '1', '1'}});

  cout << "s.maximalRectangle({{'1','0','1','1','1'},{'0','1','0','1','0'},{'1'"
          ",'1','0','1','1'},{'1','1','0','1','1'},{'0','1','1','1','1'}}) -> "
       << s.maximalRectangle(input) << '\n';  // expected output: 6

  return 0;
}
