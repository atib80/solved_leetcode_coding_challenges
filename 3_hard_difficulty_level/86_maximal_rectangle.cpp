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
#include <map>
#include <unordered_set>
#include <vector>

using namespace std;

namespace std {
template <>
struct hash<pair<size_t, size_t>> {
  uint64_t operator()(const pair<size_t, size_t>& p) const noexcept {
    uint64_t first{p.first};
    first <<= 32u;
    return first + p.second;
  }
};
}  // namespace std

class Solution {
  vector<vector<char>> matrix_{};
  size_t matrix_height{};
  size_t matrix_width{};

  int find_maximal_rectangle_in_matrix() {
    map<pair<size_t, size_t>, int> intersections{};
    unordered_set<pair<size_t, size_t>> skip_intersections{};
    int maximal_rectangle{1};

    for (const vector<char>& row : matrix_) {
      bool found_series_of_ones{};

      size_t start{string::npos};
      for (size_t y{}; y < matrix_width; y++) {
        if ('0' == row[y]) {
          if (string::npos != start && y - start > 1) {
            intersections[make_pair(start, y)]++;
            found_series_of_ones = true;
          }

          start = string::npos;
        } else if (string::npos == start && '1' == row[y])
          start = y;
      }

      if (string::npos != start && matrix_width - start > 1) {
        intersections[make_pair(start, matrix_width)]++;
        found_series_of_ones = true;
      }

      if (!found_series_of_ones) {
        intersections.clear();
        continue;
      }

      skip_intersections.clear();

      for (const auto& r : intersections) {
        if (skip_intersections.find(r.first) != end(skip_intersections))
          continue;

        pair<size_t, size_t> intersection{r.first};
        int height{r.second};
        auto current_iter = begin(intersections);

        while (current_iter != end(intersections)) {
          if (r.first == current_iter->first) {
            ++current_iter;
            continue;
          }

          if (current_iter->first.second <= intersection.first) {
            ++current_iter;
            continue;
          }

          if (current_iter->first.first >= intersection.second)
            break;

          intersection.first =
              max(intersection.first, current_iter->first.first);
          intersection.second =
              min(intersection.second, current_iter->first.second);
          height++;
          ++current_iter;
        }

        const int product{height * static_cast<int>(intersection.second -
                                                    intersection.first)};
        if (product > maximal_rectangle)
          maximal_rectangle = product;

        skip_intersections.insert(intersection);
      }
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
