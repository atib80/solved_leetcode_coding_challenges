/*
Leetcode coding challenge: First missing positive

Given an unsorted integer array, find the smallest missing positive integer.

Example 1:

Input: [1,2,0]
Output: 3

Example 2:

Input: [3,4,-1,1]
Output: 2

Example 3:

Input: [7,8,9,11,12]
Output: 1
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int firstMissingPositive(vector<int>& nums) {
    const vector<int>::iterator first{begin(nums)};
    const vector<int>::iterator last{end(nums)};
    sort(first, last);
    vector<int>::iterator start{lower_bound(first, last, 1)};

    if (last == start || 1 != *start)
      return 1;
    const int last_num{nums.back()};
    ++start;
    while (1 == *start)
      ++start;

    for (int i{2}; i <= last_num; i++) {
      const int current_num{*start};
      if (current_num != i)
        return i;
      ++start;
      while (current_num == *start)
        ++start;
    }

    return last_num + 1;
  }
};

int main() {
  Solution s{};

  vector<int> input{1, 2, 0};
  cout << s.firstMissingPositive(input) << '\n';  // expected output: 3
  input = {3, 4, -1, 1};
  cout << s.firstMissingPositive(input) << '\n';  // expected output: 2
  input = {7, 8, 9, 11, 12};
  cout << s.firstMissingPositive(input) << '\n';  // expected output: 1
  input = {0, 2, 2, 1, 1};
  cout << s.firstMissingPositive(input) << '\n';  // expected output: 3

  return 0;
}
