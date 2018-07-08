/*
221. Leetcode coding challenge: Maximal Square

Given a 2D binary matrix filled with 0's and 1's, find the largest square
containing only 1's and return its area.

Example:

Input:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 1 1 1

Output: 4
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
  int maximalSquare(vector<vector<char>>& matrix) {
    if (matrix.empty())
      return 0;

    const size_t matrix_height{matrix.size()};
    const size_t matrix_width{matrix[0].size()};

    vector<vector<pair<int, int>>> row_ones{};
    int maximal_square{};

    for (const vector<char>& row : matrix) {
      vector<pair<int, int>> ones{};
      bool found_series_of_ones{};

      size_t start{string::npos};
      for (size_t y{}; y < matrix_width; y++) {
        if ('0' == row[y]) {
          if (string::npos != start && y - start > 1) {
            ones.emplace_back(start, y);
            found_series_of_ones = true;
          }

          start = string::npos;
        } else if ('1' == row[y]) {
          if (!maximal_square)
            maximal_square = 1;
          if (string::npos == start)
            start = y;
        }
      }

      if (string::npos != start && matrix_width - start > 1) {
        ones.emplace_back(start, matrix_width);
        found_series_of_ones = true;
      }

      if (found_series_of_ones) {
        const int row_ones_size = row_ones.size();
        queue<tuple<int, int, int>> q{};

        if (row_ones_size) {
          const int ros_inc{row_ones_size + 1};
          for (size_t i{}; i < ones.size(); i++) {
            const int i_diff{ones[i].second - ones[i].first};
            const int side{min(i_diff, ros_inc)};
            if (side * side <= maximal_square)
              continue;
            q.emplace(
                make_tuple(ones[i].first, ones[i].second, row_ones_size - 1));
          }
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
            int i_width{i_last - i_start};
            const int i_height{row_ones_size - index + 1};
            if (i_width > i_height)
              i_width = i_height;
            if (i_width != i_height || 1 == i_width)
              continue;
            const int product{i_width * i_width};
            if (product > maximal_square)
              maximal_square = product;
            if (index)
              q.emplace(make_tuple(i_start, i_last, index - 1));
          }
        }

        row_ones.emplace_back(move(ones));

      } else
        row_ones.clear();
    }

    return maximal_square;
  }
};

int main() {
  Solution s{};

  vector<vector<char>> input{{'1', '0', '1', '0', '0'},
                             {'1', '0', '1', '1', '1'},
                             {'1', '1', '1', '1', '1'},
                             {'1', '0', '1', '1', '1'}};

  cout << R"(Maximal square of  
  \t['1', '0', '1', '0', '0'],
  \t['1', '0', '1', '1', '1'],
  \t['1', '1', '1', '1', '1'],
  \t['1', '0', '1', '1', '1'] is )"
       << s.maximalSquare(input) << '\n';  // expected output: 4

  return 0;
}
