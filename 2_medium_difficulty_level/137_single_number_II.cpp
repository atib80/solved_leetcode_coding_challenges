/*
137. Single number II (difficulty level: medium)

Given a non-empty array of integers, every element appears three times except
for one, which appears exactly once. Find that single one.

Note:

Your algorithm should have a linear runtime complexity. Could you implement it
without using extra memory?

Example 1:

Input:  [2,2,3,2]
Output: 3

Example 2:

Input:  [0,1,0,1,0,1,99]
Output: 99
*/

#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  Solution() { Solution::start_stop_timer(true); }

  ~Solution() {
    cout << "\nElapsed time: " << Solution::start_stop_timer() << " seconds\n";
  }

  int singleNumber(vector<int>& nums) {
    const size_t nums_size{nums.size()};

    if (1 == nums_size)
      return nums.front();

    sort(begin(nums), end(nums));

    const auto last = end(nums);
    auto prev = begin(nums);
    int target{nums.front()};
    auto next = upper_bound(prev, last, target);

    while (3 == distance(prev, next)) {
      target = *next;
      prev = next;
      next = upper_bound(prev, last, target);
    }

    return target;
  }

  static double start_stop_timer(const bool is_start_timer = false) {
    static chrono::high_resolution_clock::time_point start_time;
    if (is_start_timer)
      start_time = chrono::high_resolution_clock::now();

    return chrono::duration_cast<chrono::duration<double>>(
               chrono::high_resolution_clock::now() - start_time)
        .count();
  }
};

int main() {
  Solution s{};
  vector<int> input1{2, 2, 3, 2};
  cout << "s.singleNumber([2,2,3,2]) -> " << s.singleNumber(input1) << '\n';
  vector<int> input2{0, 1, 0, 1, 0, 1, 99};
  cout << "s.singleNumber([0,1,0,1,0,1,99]) -> " << s.singleNumber(input2)
       << '\n';

  return 0;
}
