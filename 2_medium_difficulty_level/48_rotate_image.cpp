/*

48. leetcode coding challenge: Rotate Image

You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

Note:

You have to rotate the image in-place, which means you have to modify the input
2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.

Example 1:

Given input matrix =
[
  [1,2,3],
  [4,5,6],
  [7,8,9]
],

rotate the input matrix in-place such that it becomes:
[
  [7,4,1],
  [8,5,2],
  [9,6,3]
]

Example 2:

Given input matrix =
[
  [ 5, 1, 9,11],
  [ 2, 4, 8,10],
  [13, 3, 6, 7],
  [15,14,12,16]
],

rotate the input matrix in-place such that it becomes:
[
  [15,13, 2, 5],
  [14, 3, 4, 1],
  [12, 6, 8, 9],
  [16, 7,10,11]
]
*/

#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::ostream;
using std::swap;
using std::vector;

template <typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& data) {
  os << "\n[\n";
  for (size_t i{}; i < data.size() - 1; i++) {
    os << "  [";
    for (size_t j{}; j < data[i].size() - 1; j++)
      os << data[i][j] << ',';
    os << data[i].back() << "],\n";
  }

  os << "  [";
  for (size_t j{}; j < data.back().size() - 1; j++)
    os << data.back()[j] << ',';
  os << data.back().back() << "]\n]\n";

  return os;
}

class Solution {
 public:
  void rotate(vector<vector<int>>& matrix) {
    if (matrix.empty() || matrix.size() != matrix.front().size())
      return;
    const size_t highest_index{matrix.size() - 1};
    size_t min_index{}, max_index{highest_index};

    while (min_index < max_index) {
      if (max_index - min_index == 1) {
        int temp{matrix[min_index][min_index]};
        swap(matrix[min_index][max_index], temp);
        swap(matrix[max_index][max_index], temp);
        swap(matrix[max_index][min_index], temp);
        swap(matrix[min_index][min_index], temp);
        break;
      }

      for (size_t i{min_index}; i < max_index; i++) {
        int temp{matrix[min_index][i]};
        swap(matrix[i][highest_index - min_index], temp);
        swap(matrix[highest_index - min_index][highest_index - i], temp);
        swap(matrix[highest_index - i][min_index], temp);
        swap(matrix[min_index][i], temp);
      }

      min_index++;
      max_index--;
    }
  }
};

int main() {
  Solution s{};

  vector<vector<int>> matrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  s.rotate(matrix);

  cout << "s.rotate({{1,2,3}, {4,5,6}, {7,8,9}}) -> " << matrix << '\n';

  matrix.assign(
      {{5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}});

  s.rotate(matrix);

  cout << "s.rotate({{5, 1, 9, 11}, {2, 4, 8,10}, {13, 3, 6, 7}, "
          "{15,14,12,16}}) -> "
       << matrix << '\n';

  return 0;
}
