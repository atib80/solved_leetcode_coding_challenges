/*
126. Leetcode coding challenge: Single number

Given a non-empty array of integers, every element appears twice except for one.
Find that single one.

Note:

Your algorithm should have a linear runtime complexity. Could you implement it
without using extra memory?

Example 1:

Input: [2,2,1]
Output: 1

Example 2:

Input: [4,1,2,1,2]
Output: 4
*/

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int singleNumber(vector<int>& nums) {
    const size_t nums_size{nums.size()};

    if (1 == nums_size)
      return nums.front();

    sort(begin(nums), end(nums));
    
    const auto last = end(nums);
    auto prev = begin(nums);
    int target{nums.front()};
    auto next = upper_bound(prev, last, target);

    while (distance(prev, next) > 1) {
      target = *next;
      prev = next;
      next = upper_bound(prev, last, target);
    }

    return target;
  }
};

int main() {
  Solution s{};

  vector<int> input{2, 2, 1};

  cout << "s.singleNumber({2,2,1}) -> " << s.singleNumber(input)
       << '\n';  // expected output: 1
  input.assign({4, 1, 2, 1, 2});
  cout << "s.singleNumber({4,1,2,1,2}) -> " << s.singleNumber(input)
       << '\n';  // expected output: 4

  return 0;
}
