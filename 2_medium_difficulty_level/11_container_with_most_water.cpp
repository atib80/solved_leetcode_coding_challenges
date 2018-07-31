/*
11. Leetcode coding challenge: Container with most water

Given n non-negative integers a1, a2, ..., an , where each represents a point at
coordinate (i, ai). n vertical lines are drawn such that the two endpoints of
line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis
forms a container, such that the container contains the most water.

Note: You may not slant the container and n is at least 2.

The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this
case, the max area of water (blue section) the container can contain is 49.

Example:

Input: [1,8,6,2,5,4,8,3,7]
Output: 49
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxArea(const vector<int>& height) {
    size_t left{}, right{height.size() - 1};
    int max_volume{}, high{};

    while (left < right) {
      high = min(height[right], height[left]);
      max_volume = max(max_volume, static_cast<int>(right - left) * high);

      while (left < right && height[left] <= high)
        ++left;
      while (left < right && height[right] <= high)
        --right;
    }

    return max_volume;
  }
};

int main() {
  Solution s{};

  cout << "s.maxArea({1,8,6,2,5,4,8,3,7}) -> "
       << s.maxArea({1, 8, 6, 2, 5, 4, 8, 3, 7})
       << '\n';  // expected output: 49

  return 0;
}
