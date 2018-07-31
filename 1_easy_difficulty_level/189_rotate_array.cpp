/*
189. Leetcode coding challenge: Rotate array

Given an array, rotate the array to the right by k steps, where k is
non-negative.

Example 1:

Input: [1,2,3,4,5,6,7] and k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]

Example 2:

Input: [-1,-100,3,99] and k = 2
Output: [3,99,-1,-100]
Explanation:
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]

Note:

    Try to come up as many solutions as you can, there are at least 3 different
ways to solve this problem. Could you do it in-place with O(1) extra space?
*/

#include <algorithm>
#include <chrono>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;
using namespace chrono;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& data) {
  if (data.empty()) {
    os << "data is empty\n";
    return os;
  }
  os << '[';
  for (size_t i{}; i < data.size() - 1; i++)
    os << data[i] << ',';
  os << data.back() << ']';
  return os;
}

high_resolution_clock::time_point get_current_time_point() {
  return high_resolution_clock::now();
}

double calculate_elapsed_time(high_resolution_clock::time_point const& start) {
  return duration_cast<duration<double>>(get_current_time_point() - start)
      .count();
}

class Solution {
 public:
  void rotate(vector<int>& nums, size_t k) {
    const size_t nums_size{nums.size()};

    if (!nums_size || 1u == nums_size || k == nums_size)
      return;

    if (k > nums_size)
      k %= nums_size;

    // 1. solution
    nums.reserve(nums_size + k);
    nums.resize(nums_size + k);
    copy_backward(end(nums) - 2 * k, end(nums) - k, end(nums));
    copy_backward(begin(nums), end(nums) - 2 * k, end(nums) - k);
    copy(end(nums) - k, end(nums), begin(nums));
    nums.erase(begin(nums) + nums_size, end(nums));

    // 2. solution
    // for (size_t i{}; i != k; i++) {
    //   const auto last_num{nums.back()};
    //   nums.pop_back();
    //   nums.insert(begin(nums), last_num);
    // }

    // 3. solution
    // deque<int> deq(begin(nums), end(nums));
    // for (size_t i{}; i != k; i++) {
    //   const auto last_num{deq.back()};
    //   deq.pop_back();
    //   deq.push_front(last_num);
    // }
    // nums.assign(make_move_iterator(begin(deq)), make_move_iterator(end(deq)));
  }
};

int main() {
  Solution s{};

  vector<int> input{1, 2, 3, 4, 5, 6, 7};
  const auto start{get_current_time_point()};
  s.rotate(input, 3);
  cout << "s.rotate({1,2,3,4,5,6,7}, 3) -> " << input
       << "\nRunning time: " << calculate_elapsed_time(start)
       << " sec.\n";  // expected output: [4, 5, 6, 7, 1, 2, 3]

  return 0;
}
