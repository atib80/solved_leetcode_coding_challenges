/*
169. Leetcode coding challenge: Majority element

Given an array of size n, find the majority element. The majority element is the
element that appears more than ⌊ n/2 ⌋ times.

You may assume that the array is non-empty and the majority element always exist
in the array.

Example 1:

Input: [3,2,3]
Output: 3

Example 2:

Input: [2,2,1,1,1,2,2]
Output: 2
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int majorityElement(vector<int>& nums) {
    sort(begin(nums), end(nums));

    auto current{cbegin(nums)};
    const auto last{cend(nums)};
    auto next{upper_bound(current, last, *current)};

    int majority_element{*current};
    int majority_element_count{static_cast<int>(distance(current, next))};

    while (next != last) {
      current = next;
      next = upper_bound(current, last, *current);
      const int next_element_count{static_cast<int>(distance(current, next))};
      if (next_element_count > majority_element_count) {
        majority_element = *current;
        majority_element_count = next_element_count;
      }
    }

    return majority_element;
  }
};

int main() {
  Solution s{};
  vector<int> input1{3, 2, 3};
  cout << "s.majorityElement({3,2,3}) -> " << s.majorityElement(input1)
       << '\n';  // expected output: 3

  vector<int> input2{2, 2, 1, 1, 1, 2, 2};
  cout << "s.majorityElement(2,2,1,1,1,2,2) -> " << s.majorityElement(input2)
       << '\n';  // expected output: 2

  return 0;
}