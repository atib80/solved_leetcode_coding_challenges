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
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

static int sres = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

class Solution {
 public:
  int maximalRectangle(vector<vector<char>>& matrix) {
    if (matrix.empty())
      return 0;
    const size_t matrix_height{matrix.size()};
    const size_t matrix_width{matrix[0].size()};

    vector<vector<pair<int, int>>> row_ones{};
    vector<int> single_ones_height(matrix_width, 0);
    int maximal_rectangle{};

    for (const vector<char>& row : matrix) {
      vector<pair<int, int>> ones{};
      bool found_series_of_ones{};

      size_t start{string::npos};
      for (size_t y{}; y < matrix_width; y++) {
        if ('0' == row[y]) {
          single_ones_height[y] = 0;
          if (string::npos != start && y - start > 1) {
            ones.emplace_back(start, y);
            found_series_of_ones = true;
          }

          start = string::npos;
        } else if ('1' == row[y]) {
          single_ones_height[y]++;
          if (single_ones_height[y] > maximal_rectangle)
            maximal_rectangle = single_ones_height[y];
          if (string::npos == start) {
            start = y;
          }
        }
      }

      if (string::npos != start && matrix_width - start > 1) {
        ones.emplace_back(start, matrix_width);
        found_series_of_ones = true;
      }

      if (found_series_of_ones) {
        queue<tuple<int, int, int>> q{};
        const int row_ones_size = row_ones.size();
        for (size_t i{}; i < ones.size(); i++) {
          const int product{ones[i].second - ones[i].first};
          if (product * (row_ones_size + 1) <= maximal_rectangle)
            continue;
          if (product > maximal_rectangle)
            maximal_rectangle = product;
          if (row_ones_size)
            q.emplace(
                make_tuple(ones[i].first, ones[i].second, row_ones_size - 1));
        }

        while (!q.empty()) {
          const int first{get<0>(q.front())};
          const int last{get<1>(q.front())};
          const int index{get<2>(q.front())};
          q.pop();

          for (size_t i{}; i < row_ones[index].size(); i++) {
            if (first >= row_ones[index][i].second)
              continue;

            if (last <= row_ones[index][i].first)
              break;

            const int i_start{max(first, row_ones[index][i].first)};
            const int i_last{min(last, row_ones[index][i].second)};
            const int i_diff{i_last - i_start};
            if (1 == i_diff)
              continue;
            const int product{(row_ones_size - index + 1) * i_diff};
            if (product > maximal_rectangle)
              maximal_rectangle = product;
            if (index)
              q.emplace(make_tuple(i_start, i_last, index - 1));
          }
        }

        row_ones.emplace_back(move(ones));

      } else
        row_ones.clear();
    }

    return maximal_rectangle;
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

  input.assign({{'0', '1'}, {'0', '1'}});
  cout << "s.maximalRectangle({{'0','1'},{'0','1'}}) -> "
       << s.maximalRectangle(input) << '\n';  // expected output: 2

  // 1 - 3 | 0 - 2 | 1 - 4 | 0 - 4 | 0 - 5

  input.assign({{'0', '1', '1', '0', '1'},
                {'1', '1', '0', '1', '0'},
                {'0', '1', '1', '1', '0'},
                {'1', '1', '1', '1', '0'},
                {'1', '1', '1', '1', '1'},
                {'0', '0', '0', '0', '0'}});
  cout << "s.maximalRectangle({{'0','1','1','0','1'},{'1','1','0','1','0'},{'0'"
          ",'1','1','1','0'},{'1','1','1','1','0'},{'1','1','1','1','1'},{'0','"
          "0','0','0','0'}}) -> "
       << s.maximalRectangle(input) << '\n';  // expected output: 9

  return 0;
}
