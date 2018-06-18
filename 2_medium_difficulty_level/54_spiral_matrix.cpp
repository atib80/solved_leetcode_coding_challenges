/*
54. Leetcode coding challenge: Spiral Matrix

Given a matrix of m x n elements (m rows, n columns), return all elements of the
matrix in spiral order.

Example 1:

Input:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]

Output: [1,2,3,6,9,8,7,4,5]

Example 2:

Input:
[
  [1, 2, 3, 4],
  [5, 6, 7, 8],
  [9,10,11,12]
]

Output: [1,2,3,4,8,12,11,10,9,5,6,7]
*/

#include <algorithm>
#include <iostream>
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
  os << '[';
  for (size_t i{}; i < data.size() - 1; i++)
    os << data[i] << ',';
  os << data.back() << "]\n";
  return os;
}

class Solution {
 public:
  vector<int> spiralOrder(vector<vector<int>>& matrix) {
    if (matrix.empty())
      return vector<int>{};
    if (1 == matrix.size())
      return move(matrix.front());
    if (2 == matrix.size()) {
      vector<int> result{move(matrix[0])};
      copy(rbegin(matrix[1]), rend(matrix[1]), back_inserter(result));
      return result;
    }

    int min_x{}, max_x{static_cast<int>(matrix.size() - 1)};
    int min_y{}, max_y{static_cast<int>(matrix[0].size() - 1)};

    const size_t max_cells{matrix.size() * matrix[0].size()};

    vector<int> result(max_cells);

    // starting point is the upper-left corner of 'matrix' (min_x, min_y)
    int x{}, y{};

    size_t cells_visited{};

    while (true) {
      while (y <= max_y && cells_visited < max_cells) {
        result[cells_visited] = matrix[x][y];
        cells_visited++;
        y++;
      }

      if (max_cells == cells_visited)
        break;

      min_x++;  // we increase min_x by 1 so that we don't accidentally wind up
                // visiting the previously visited top row again
      x = min_x;
      y = max_y;

      while (x <= max_x && cells_visited < max_cells) {
        result[cells_visited] = matrix[x][y];
        cells_visited++;
        x++;
      }

      if (max_cells == cells_visited)
        break;

      max_y--;  // we decrease max_y by 1 so that we don't accidentally wind up
                // visiting the previously visited right column again
      y = max_y;
      x = max_x;

      while (y >= min_y && cells_visited < max_cells) {
        result[cells_visited] = matrix[x][y];
        cells_visited++;
        y--;
      }

      if (max_cells == cells_visited)
        break;

      max_x--;  // we decrease max_x by 1 so that we don't accidentally wind up
                // visiting the previously visited bottom row again
      x = max_x;
      y = min_y;

      while (x >= min_x && cells_visited < max_cells) {
        result[cells_visited] = matrix[x][y];
        cells_visited++;
        x--;
      }

      if (max_cells == cells_visited)
        break;

      min_y++;  // we increase min_y by 1 so that we don't accidentally wind up
                // visiting the previously visited left column again
      y = min_y;
      x = min_x;
    }

    return result;
  }
};

int main() {
  Solution s{};

  vector<vector<int>> matrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  vector<int> output{s.spiralOrder(matrix)};

  cout << "s.spiralOrder(matrix) -> " << output
       << '\n';  // expected output: [1,2,3,6,9,8,7,4,5]

  matrix.assign({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}});

  output = s.spiralOrder(matrix);

  cout << "s.spiralOrder(matrix) -> " << output
       << '\n';  // expected output: [1,2,3,4,8,12,11,10,9,5,6,7]

  matrix.assign({{1, 2, 3, 4}, {5, 6, 7, 8}});

  output = s.spiralOrder(matrix);

  cout << "s.spiralOrder(matrix) -> " << output
       << '\n';  // expected output: [1,2,3,4,8,7,6,5]

  return 0;
}
