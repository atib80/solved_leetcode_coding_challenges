/*
Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one
sorted array.

Note:

    The number of elements initialized in nums1 and nums2 are m and n
respectively. You may assume that nums1 has enough space (size that is greater
or equal to m + n) to hold additional elements from nums2.

Example:

Input:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3

Output: [1,2,2,3,5,6]
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& data) {
  if (data.empty()) {
    os << "data is empty\n";
    return os;
  }
  os << "\n  [";
  for (size_t i{}; i < data.size() - 1; i++)
    os << data[i] << ',';
  os << data.back() << "]";
  return os;
}

class Solution {
 public:
  void merge(vector<int>& nums1,
             const size_t m,
             vector<int>& nums2,
             const size_t n) {
    const size_t m_plus_n{m + n};
    if (nums1.size() < m_plus_n)
      nums1.resize(m_plus_n);
    move(begin(nums2), begin(nums2) + n, begin(nums1) + m);
    inplace_merge(begin(nums1), begin(nums1) + m, begin(nums1) + m + n);
  }
};

int main() {
  Solution s{};

  vector<int> v1{1, 2, 3, 0, 0, 0};
  vector<int> v2{2, 5, 6};
  s.merge(v1, 3, v2, 3);
  cout << "s.merge({1,2,3,0,0,0}, 3, {2,5,6}, 3) -> " << v1 << '\n';

  return 0;
}
