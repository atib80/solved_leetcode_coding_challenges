/*
120. Triangle (difficulty level: medium)

Given a triangle, find the minimum path sum from top to bottom. Each step you
may move to adjacent numbers on the row below.

For example, given the following triangle

[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]

The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Note:

Bonus point if you are able to do this using only O(n) extra space, where n is
the total number of rows in the triangle.
*/

#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
  vector<vector<int>> triangle_;
  size_t number_of_rows_;
  int min_path_sum_;

  void find_minimum_path_sum(const size_t row_index,
                             const size_t column_index,
                             int path_sum = 0) {
    if (row_index == number_of_rows_) {
      if (path_sum < min_path_sum_)
        min_path_sum_ = path_sum;
      return;
    }

    path_sum += triangle_[row_index][column_index];

    find_minimum_path_sum(row_index + 1, column_index, path_sum);
    find_minimum_path_sum(row_index + 1, column_index + 1, path_sum);
  }

 public:
  int minimumTotal(const vector<vector<int>>& triangle) {
    triangle_ = move(triangle);
    number_of_rows_ = triangle_.size();
    if (!number_of_rows_)
      return 0;
    if (1 == number_of_rows_) {
      if (!triangle_[0].empty())
        return triangle_[0][0];
      return 0;
    }
    min_path_sum_ = numeric_limits<int>::max();
    find_minimum_path_sum(0, 0);
    return min_path_sum_;
  }
};

int main() {
  Solution s{};

  vector<vector<int>> input{{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
  cout << "s.minimumTotal([[2], [3,4], [6,5,7], [4,1,8,3]]) -> "
       << s.minimumTotal(input) << '\n';  // expected output: 11

  return 0;
}
