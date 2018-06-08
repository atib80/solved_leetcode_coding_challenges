/*
Given an array of integers nums sorted in ascending order, find the starting and
ending position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

Example 1:

Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]

Example 2:

Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]
*/
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::distance;
using std::equal_range;
using std::ostream;
using std::string;
using std::vector;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& container) {
  auto first = begin(container);
  auto last = end(container);
  --last;
  os << '{';
  while (first != last) {
    os << *first << ',';
    ++first;
  }

  os << *first << '}';

  return os;
}

class Solution {
 public:
  vector<int> searchRange(const vector<int>& nums, const int target) {
    const auto first = begin(nums);
    const auto last = end(nums);

    auto iter_pair = equal_range(first, last, target);

    if (iter_pair.first == last || *(iter_pair.first) != target)
      return {-1, -1};

    --iter_pair.second;

    return {distance(first, iter_pair.first),
            distance(first, iter_pair.second)};
  }
};

int main() {
  Solution s{};

  cout << "s.searchRange({5,7,7,8,8,10}, 8) -> ";
  vector<int> result{s.searchRange(vector<int>{5, 7, 7, 8, 8, 10},
                                   8)};  // expected output: 3,4

  cout << result << '\n';

  cout << "s.searchRange({5,7,7,8,8,10}, 6) -> ";
  result = s.searchRange(vector<int>{5, 7, 7, 8, 8, 10},
                         6);  // expected output: -1,-1
  cout << result << "\n\n";

  return 0;
}