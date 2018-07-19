/*
81. Leetcode coding challenge: Search in rotated array II

Suppose an array sorted in ascending order is rotated at some pivot unknown to
you beforehand.

(i.e., [0,0,1,2,2,5,6] might become [2,5,6,0,0,1,2]).

You are given a target value to search. If found in the array return true,
otherwise return false.

Example 1:

Input: nums = [2,5,6,0,0,1,2], target = 0
Output: true

Example 2:

Input: nums = [2,5,6,0,0,1,2], target = 3
Output: false

Follow up:

This is a follow up problem to Search in Rotated Sorted Array, where nums
may contain duplicates. Would this affect the run-time complexity? How and why?
*/

#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

static int sres = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

template <typename ForwardIter, typename T>
bool bsearch(ForwardIter first, ForwardIter last, T value) {
  if (first >= last)
    return false;

  ForwardIter next{first};

  while (++next < last) {
    ForwardIter current{first};

    advance(current, distance(first, last) / 2);

    if (value < *current)
      last = current;
    else
      first = current;

    next = first;
  }

  if (value == *first)
    return true;

  return false;
}

class Solution {
 public:
  bool search(const vector<int>& nums, const int target) {
    const size_t nums_size{nums.size()};
    if (!nums_size)
      return false;
    if (1 == nums_size) {
      if (nums.front() == target)
        return true;
      return false;
    }

    const auto nums_first{cbegin(nums)};
    const auto nums_last{cend(nums)};
    auto first{nums_first}, prev{nums_first}, next{nums_first};

    while (++next < nums_last) {
      if (*next < *prev) {
        first = next;
        break;
      }

      prev = next;
    }

    if (nums_first == first)
      return bsearch(nums_first, nums_last, target);

    return bsearch(nums_first, first, target) ||
           bsearch(first, nums_last, target);
  }
};

int main() {
  Solution s{};

  const vector<int> numbers{2, 5, 6, 0, 0, 1, 2};
  cout << boolalpha << "s.search({2,5,6,0,0,1,2}, 0) -> "
       << s.search(numbers, 0) << '\n'  // expected output: true
       << "s.search({2,5,6,0,0,1,2}, 3) -> " << s.search(numbers, 3)
       << '\n'  // expected output: false
       << "s.search({1,2,1}, 2) -> " << s.search({1, 2, 1}, 2)
       << '\n'  // expected output: true
       << "s.search({1,1,3}, 3) -> " << s.search({1, 1, 3}, 3)
       << '\n'  // expected output: true
       << "s.search({3,1,1}, 3) -> " << s.search({3, 1, 1}, 3)
       << '\n'  // expected output: true
       << "s.search({2,2,2,0,2,2}, 0) -> " << s.search({2, 2, 2, 0, 2, 2}, 0)
       << '\n'  // expected output: true
       << noboolalpha;

  return 0;
}
