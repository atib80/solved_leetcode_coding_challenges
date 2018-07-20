/*
Given n non-negative integers representing the histogram's bar height where the
width of each bar is 1, find the area of largest rectangle in the histogram.

Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].

The largest rectangle is shown in the shaded area, which has area = 10 unit.

Example:

Input: [2,1,5,6,2,3]
Output: 10
*/

#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  int largestRectangleArea(const vector<int>& heights) {
    unordered_set<int> already_visited_heights{};
    const size_t heights_size{heights.size()};
    int max_area{};

    for (size_t i{}; i < heights_size; i++) {
      if (already_visited_heights.count(heights[i]))
        continue;

      if (heights[i] * heights_size <= max_area)
        continue;
      already_visited_heights.insert(heights[i]);
      int current_area{};

      for (size_t j{}; j < heights_size; j++) {
        if (heights[j] < heights[i]) {
          if (current_area > max_area)
            max_area = current_area;
          current_area = 0;

        } else
          current_area += heights[i];
      }

      if (current_area > max_area)
        max_area = current_area;
    }

    return max_area;
  }
};

int main() {
  Solution s{};

  vector<int> heights{2, 1, 5, 6, 2, 3};
  cout << "s.largestRectangleArea({2,1,5,6,2,3}) -> "
       << s.largestRectangleArea(heights) << '\n';  // expected output: 10

  return 0;
}
