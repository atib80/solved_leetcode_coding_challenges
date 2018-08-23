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

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int minimumTotal(vector<vector<int>>& triangle) const {
    const size_t number_of_rows{triangle.size()};
    if (!number_of_rows)
      return 0;
    if (1 == number_of_rows) {
      if (!triangle[0].empty())
        return triangle[0][0];
      return 0;
    }

    triangle[1][0] += triangle[0][0];
    triangle[1][1] += triangle[0][0];

    for (size_t i{2}; i < number_of_rows; i++) {
      triangle[i][0] += triangle[i - 1][0];
      int left_path_sum{triangle[i - 1][0] + triangle[i][1]};

      for (size_t y{1}; y < triangle[i - 1].size(); y++) {
        triangle[i][y] =
            min(left_path_sum, triangle[i - 1][y] + triangle[i][y]);
        if (y < triangle[i - 1].size() - 1)
          left_path_sum = triangle[i - 1][y] + triangle[i][y + 1];
        else
          break;
      }

      triangle[i].back() += triangle[i - 1].back();
    }

    return *min_element(begin(triangle.back()), end(triangle.back()));
  }
};

int main() {
  Solution s{};

  vector<vector<int>> input{{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
  cout << "s.minimumTotal([[2], [3,4], [6,5,7], [4,1,8,3]]) -> "
       << s.minimumTotal(input) << '\n';  // expected output: 11

  input.assign({{2}, {3, 4}, {6, 5, 9}, {4, 4, 8, 0}});
  cout << "s.minimumTotal([[2],[3,4],[6,5,9],[4,4,8,0]]) -> "
       << s.minimumTotal(input) << '\n';  // expected output: 14

  input.assign({{-1}, {2, 3}, {1, -1, -3}});
  cout << "s.minimumTotal([[-1],[2,3],[1,-1,-3]]) -> " << s.minimumTotal(input)
       << '\n';  // expected output: -1

  input.assign({{-7},
                {-2, 1},
                {-5, -5, 9},
                {-4, -5, 4, 4},
                {-6, -6, 2, -1, -5},
                {3, 7, 8, -3, 7, -9},
                {-9, -1, -9, 6, 9, 0, 7},
                {-7, 0, -6, -8, 7, 1, -4, 9},
                {-3, 2, -6, -9, -7, -6, -9, 4, 0},
                {-8, -6, -3, -9, -2, -6, 7, -5, 0, 7},
                {-9, -1, -2, 4, -2, 4, 4, -1, 2, -5, 5},
                {1, 1, -6, 1, -2, -4, 4, -2, 6, -6, 0, 6},
                {-3, -3, -6, -2, -6, -2, 7, -9, -5, -7, -5, 5, 1}});
  cout << "s.minimumTotal([-7],[-2,1],[-5,-5,9],[-4,-5,4,4],[-6,-6,2,-1,-5],["
          "3,7,8,-3,7,-9],[-9,-1,-9,6,9,0,7],[-7,0,-6,-8,7,1,-4,9],[-3,2,-6,-9,"
          "-7,-6,-9,4,0],[-8,-6,-3,-9,-2,-6,7,-5,0,7],[-9,-1,-2,4,-2,4,4,-1,2,-"
          "5,5],[1,1,-6,1,-2,-4,4,-2,6,-6,0,6],[-3,-3,-6,-2,-6,-2,7,-9,-5,-7,-"
          "5,5,1]]) -> "
       << s.minimumTotal(input) << '\n';  // expected output: -63

  return 0;
}
