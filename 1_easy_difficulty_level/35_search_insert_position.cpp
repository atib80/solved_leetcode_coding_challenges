/*
Leetcode coding challenge: Search insert position

Given a sorted array and a target value, return the index if the target is
found. If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Example 1:

Input: [1,3,5,6], 5
Output: 2

Example 2:

Input: [1,3,5,6], 2
Output: 1

Example 3:

Input: [1,3,5,6], 7
Output: 4

Example 4:

Input: [1,3,5,6], 0
Output: 0
*/

#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::distance;
using std::lower_bound;
using std::vector;

class Solution {
 public:
  int searchInsert(const vector<int>& nums, const int target) {
    const auto first = begin(nums);
    const auto last = end(nums);
    auto lb_iter = lower_bound(first, last, target);

    if (lb_iter != last)
      return distance(first, lb_iter);

    return nums.size();
  }
};

int main() {
  Solution s{};

  cout << s.searchInsert(vector<int>{1, 3, 5, 6}, 5)
       << '\n';  // expected output: 2
  cout << s.searchInsert(vector<int>{1, 3, 5, 6}, 2)
       << '\n';  // expected output: 1
  cout << s.searchInsert(vector<int>{1, 3, 5, 6}, 7)
       << '\n';  // expected output: 4
  cout << s.searchInsert(vector<int>{1, 3, 5, 6}, 0)
       << '\n';  // expected output: 0

  return 0;
}