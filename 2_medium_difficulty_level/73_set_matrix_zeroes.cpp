/*
Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do
it in-place.

Example 1:

Input:
[
  [1,1,1],
  [1,0,1],
  [1,1,1]
]
Output:
[
  [1,0,1],
  [0,0,0],
  [1,0,1]
]

Example 2:

Input:
[
  [0,1,2,0],
  [3,4,5,2],
  [1,3,1,5]
]
Output:
[
  [0,0,0,0],
  [0,4,5,0],
  [0,3,1,0]
]

Follow up:

    A straight forward solution using O(mn) space is probably a bad idea.
    A simple improvement uses O(m + n) space, but still not the best solution.
    Could you devise a constant space solution?
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

static int sres = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  return 0;
}();

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& data) {
  if (data.empty()) {
    os << "data is empty\n";
    return os;
  }
  os << "\n[";
  for (size_t i{}; i < data.size() - 1; i++)
    os << data[i] << ',';
  os << data.back() << "]\n";
  return os;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& data) {
  if (data.empty()) {
    os << "data is empty\n";
    return os;
  }
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
  static void zero_out_a_row(vector<vector<int>>& matrix,
                             const size_t matrix_height,
                             const size_t matrix_width,
                             const size_t i,
                             vector<size_t>& columns_zeroed_out) {
    if (i > matrix_height)
      return;

    for (size_t j{}; j < matrix_width; j++) {
      if (!matrix[i][j])
        columns_zeroed_out[j] = 1;
      matrix[i][j] = 0;
    }
  }

 public:
  void setZeroes(vector<vector<int>>& matrix) {
    if (matrix.empty())
      return;
    const size_t matrix_height{matrix.size()};
    const size_t matrix_width{matrix[0].size()};
    if (1 == matrix_height && 1 == matrix_width)
      return;

    vector<size_t> columns_zeroed_out(matrix_width, 0);

    for (size_t i{}; i < matrix_height; i++) {
      for (size_t j{}; j < matrix_width; j++) {
        if (!matrix[i][j]) {
          zero_out_a_row(matrix, matrix_height, matrix_width, i,
                         columns_zeroed_out);
          break;
        }
      }
    }

    for (size_t j{}; j < matrix_width; j++) {
      if (!columns_zeroed_out[j])
        continue;
      for (size_t i{}; i < matrix_height; i++)
        matrix[i][j] = 0;
    }
  }
};

int main() {
  Solution s{};

  vector<vector<int>> input{{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};

  s.setZeroes(input);

  cout << "s.setZeroes(\n"
          "[\n"
          "  [1,1,1],\n"
          "  [1,0,1],\n"
          "  [1,1,1]\n"
          "] ) -> "
       << input << '\n';

  input.assign({{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}});

  s.setZeroes(input);

  cout << "s.setZeroes(\n"
          "[\n"
          "  [0,1,2,0],\n"
          "  [3,4,5,2],\n"
          "  [1,3,1,5]\n"
          "] ) -> "
       << input << '\n';

  return 0;
}