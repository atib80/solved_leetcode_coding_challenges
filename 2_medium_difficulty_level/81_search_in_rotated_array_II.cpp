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

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

static int sres = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

template <typename T>
bool binary_search_with_offset(const vector<T>& buffer,
                               const size_t buffer_size,
                               const T& value,
                               const size_t offset = 0) {
  size_t first{offset}, last{offset + buffer_size}, next{offset};

  while (++next < last) {
    size_t current{first};

    current += (last - first) / 2;

    if (value < buffer[current % buffer_size])
      last = current;
    else
      first = current;

    next = first;
  }

  if (value == buffer[first % buffer_size])
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

    size_t first{static_cast<size_t>(min_element(cbegin(nums), cend(nums)) -
                                     cbegin(nums))};

    const int first_element{nums[first]};

    size_t last{static_cast<size_t>(max_element(cbegin(nums), cend(nums)) -
                                    cbegin(nums))};

    if (last > first && last < nums_size - 1) {
      size_t last_first{last};
      while (++last_first < nums_size) {
        if (first_element == nums[last_first]) {
          first = last_first;
          break;
        }
      }
    }

    return binary_search_with_offset(nums, nums_size, target, first);
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
