/*
128. Longest consecutive sequence (difficulty level: hard)

Given an unsorted array of integers, find the length of the longest consecutive
elements sequence.

Your algorithm should run in O(n) complexity.

Example:

Input: [100, 4, 200, 1, 3, 2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4].
Therefore its length is 4.
*/

#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int longestConsecutive(const vector<int>& nums) {
    if (nums.size() < 2)
      return nums.size();

    unordered_map<int, int> range_intervals{};

    int max_lcs_length{1};

    for (const int n : nums) {
      if (range_intervals.find(n) != end(range_intervals))
        continue;

      range_intervals[n] = n;

      const auto lb_iter{range_intervals.find(n - 1)};

      if (lb_iter != end(range_intervals)) {
        const int lower_bound_val{lb_iter->second};
        const int upper_bound_val{range_intervals.at(n)};
        range_intervals[upper_bound_val] = lower_bound_val;
        range_intervals[lower_bound_val] = upper_bound_val;
        const int lb_seq_len{abs(upper_bound_val - lower_bound_val) + 1};
        if (lb_seq_len > max_lcs_length)
          max_lcs_length = lb_seq_len;
      }
      const auto ub_iter{range_intervals.find(n + 1)};

      if (ub_iter != end(range_intervals)) {
        const int upper_bound_val{ub_iter->second};
        const int lower_bound_val{range_intervals.at(n)};
        range_intervals[lower_bound_val] = upper_bound_val;
        range_intervals[upper_bound_val] = lower_bound_val;
        const int ub_seq_len{abs(upper_bound_val - lower_bound_val) + 1};
        if (ub_seq_len > max_lcs_length)
          max_lcs_length = ub_seq_len;
      }
    }

    return max_lcs_length;
  }
};

int main() {
  Solution s{};
  cout << "s.longestConsecutive([100, 4, 200, 1, 3, 2]) -> "
       << s.longestConsecutive({100, 4, 200, 1, 3, 2})
       << '\n';  // expected output: 4
  cout << "s.longestConsecutive([2, 4, 6, 5, 8, 9]) -> "
       << s.longestConsecutive({2, 4, 6, 5, 8, 9})
       << '\n';  // expected output: 3
  cout << "s.longestConsecutive([2, 3]) -> " << s.longestConsecutive({2, 3})
       << '\n';  // expected output: 2
  cout << "s.longestConsecutive([2, 4]) -> " << s.longestConsecutive({2, 4})
       << '\n';  // expected output: 1
  cout << "s.longestConsecutive([1]) -> " << s.longestConsecutive({1})
       << '\n';  // expected output: 1
  cout << "s.longestConsecutive([1,3,5,2,4]) -> "
       << s.longestConsecutive({1, 3, 5, 2, 4}) << '\n';  // expected output: 5
  cout << "s.longestConsecutive([9,-8,9,8,-7,9,-4,6,5,5,6,7,-9,-5,-4,6,-8,-1,8,"
          "0,1,5,4]) -> "
       << s.longestConsecutive({9,  -8, 9,  8, -7, 9,  -4, 6, 5, 5, 6, 7,
                                -9, -5, -4, 6, -8, -1, 8,  0, 1, 5, 4})
       << '\n';  // expected output: 6

  return 0;
}
