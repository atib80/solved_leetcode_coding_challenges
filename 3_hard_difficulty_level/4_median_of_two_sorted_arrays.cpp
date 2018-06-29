/*
4. Leetcode coding challenge: Median of two sorted arrays

There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should
be O(log (m+n)).

Example 1:

nums1 = [1, 3]
nums2 = [2]

The median is 2.0

Example 2:

nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

static int sres = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

class Solution {
 public:
  double findMedianSortedArrays(vector<int>& nums1, const vector<int>& nums2) {
    size_t nums1_size{nums1.size()};
    const size_t nums_size{nums1_size + nums2.size()};
    nums1.reserve(nums_size);

    nums1.insert(end(nums1), make_move_iterator(begin(nums2)),
                 make_move_iterator(end(nums2)));
    const auto first = begin(nums1);
    const auto last = end(nums1);
    inplace_merge(first, first + nums1_size, last);

    if (nums_size % 2 == 1)
      return static_cast<double>(nums1[nums_size / 2]);

    return (nums1[nums_size / 2] + nums1[nums_size / 2 - 1]) / 2.0;
  }
};

int main() {
  Solution s{};
  vector<int> input1{1, 3};
  vector<int> input2{2};

  cout << "s.findMedianSortedArrays({1, 3}, {2}) -> "
       << s.findMedianSortedArrays(input1, input2)
       << '\n';  // expected output: 2.0

  input1.assign({1, 2});
  input2.assign({3, 4});

  cout << "s.findMedianSortedArrays({1, 2}, {3, 4}) -> "
       << s.findMedianSortedArrays(input1, input2)
       << '\n';  // expected output: 2.5

  return 0;
}
