/*
Write an efficient algorithm that searches for a value in an m x n matrix. This
matrix has the following properties:

    Integers in each row are sorted from left to right.
    The first integer of each row is greater than the last integer of the
previous row.

Example 1:

Input:
matrix = [
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
target = 3
Output: true

Example 2:

Input:
matrix = [
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]

target = 13
Output: false
*/

#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

static int sres = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  return 0;
}();

template <typename T>
bool binary_search(const vector<vector<T>>& matrix,
                   const size_t matrix_height,
                   const size_t matrix_width,
                   const T& value) {
  size_t first{}, last{matrix_height * matrix_width}, next{};

  while (++next < last) {
    size_t current{first};

    current += (last - first) / 2;

    if (value < matrix[current / matrix_width][current % matrix_width])
      last = current;
    else
      first = current;

    next = first;
  }

  if (value == matrix[first / matrix_width][first % matrix_width])
    return true;

  return false;
}

class Solution {
 public:
  bool searchMatrix(vector<vector<int>>& matrix, const int target) {
    const size_t matrix_height{matrix.size()};
    if (!matrix_height)
      return false;
    const size_t matrix_width{matrix[0].size()};
    if (1 == matrix_width && 1 == matrix_height) {
      if (target == matrix[0][0])
        return true;
      return false;
    }

    return binary_search(matrix, matrix_height, matrix_width, target);
  }
};

int main() {
  Solution s{};

  vector<vector<int>> input{{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 50}};
  cout << boolalpha
       << "s.searchMatrix(vector<vector<int>>{{1, 3,  5,  7},{10, 11, 16, "
          "20},{23, 30, 34, 50}}, 3) -> "
       << s.searchMatrix(input, 3) << '\n';  // expected output: true
  cout << "s.searchMatrix(vector<vector<int>>{{1, 3,  5,  7},{10, 11, 16, "
          "20},{23, 30, 34, 50}}, 13) -> "
       << s.searchMatrix(input, 13) << noboolalpha
       << '\n';  // expected output: false

  return 0;
}
