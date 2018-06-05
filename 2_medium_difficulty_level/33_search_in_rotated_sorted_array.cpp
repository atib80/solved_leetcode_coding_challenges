/*
Leetcode coding challenge: Search in rotated sorted array

Suppose an array sorted in ascending order is rotated at some pivot unknown to
you beforehand.

(i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).

You are given a target value to search. If found in the array return its index,
otherwise return -1.

You may assume no duplicate exists in the array.

Your algorithm's runtime complexity must be in the order of O(log n).

Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Example 2:

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
*/

#include <algorithm>
// #include <execution>
#include <iostream>
#include <type_traits>
#include <vector>

template <typename ForwardIter, typename T>
ForwardIter optimal_bsearch(ForwardIter first,
                            ForwardIter last,
                            const T& value) {
  using difference_type =
      typename std::iterator_traits<ForwardIter>::difference_type;

  const ForwardIter orig_last{last};
  ForwardIter next{first};

  while (++next < last) {
    ForwardIter current{first};

    const difference_type d{std::distance(first, last)};

    std::advance(current, d / 2);

    if (value < *current)
      last = current;
    else
      first = current;

    next = first;
  }

  if (value == *first)
    return first;

  return orig_last;
}

class Solution {
 public:
  int search(std::vector<int>& nums, const int target) {
    const size_t nums_size{nums.size()};

    if (!nums_size)
      return -1;

    if (nums_size < 3) {
      if (1 == nums_size && target == nums.front())
        return 0;
      if (2 == nums_size) {
        if (target == nums.front())
          return 0;
        if (target == nums.back())
          return 1;
      }
      return -1;
    }

    const std::vector<int>::iterator first{std::begin(nums)};
    const std::vector<int>::iterator last{std::end(nums)};
    // const std::vector<int>::iterator
    // middle{std::is_sorted_until(std::execution::par, first, last)};
    const std::vector<int>::iterator middle{std::is_sorted_until(first, last)};

    std::vector<int>::iterator found_iter{
        optimal_bsearch(first, middle, target)};
    if (middle != found_iter)
      return std::distance(first, found_iter);

    found_iter = optimal_bsearch(middle, last, target);
    if (last != found_iter)
      return std::distance(first, middle) + std::distance(middle, found_iter);

    return -1;
  }
};

int main() {
  Solution s{};

  std::vector<int> v{4, 5, 6, 7, 0, 1, 2};

  std::cout << "s.search({4,5,6,7,0,1,2}, 0) -> " << s.search(v, 0)
            << '\n';  // expected output: 4
  std::cout << "s.search({4,5,6,7,0,1,2}, 3) -> " << s.search(v, 3)
            << '\n';  // expected output: -1

  return 0;
}
