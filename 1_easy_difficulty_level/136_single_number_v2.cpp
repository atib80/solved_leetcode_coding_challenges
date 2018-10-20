/*
126. Leetcode coding challenge: Single number

Given a non-empty array of integers, every element appears twice except for one.
Find that single one.

Note:

Your algorithm should have a linear runtime complexity. Could you implement it
without using extra memory?

Example 1:

Input: [2,2,1]
Output: 1

Example 2:

Input: [4,1,2,1,2]
Output: 4
*/

#include <algorithm>
#include <chrono>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  int singleNumber(const vector<int>& nums) {
    if (0u == nums.size())
      return 0;

    unordered_set<int> already_seen_numbers{};

    for (const int n : nums) {
      if (already_seen_numbers.count(n))
        already_seen_numbers.erase(n);
      else
        already_seen_numbers.emplace(n);
    }

    return *begin(already_seen_numbers);
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
  Solution::start_stop_timer(true);

  vector<int> input{2, 2, 1};

  cout << "s.singleNumber({2,2,1}) -> " << s.singleNumber(input)
       << '\n';  // expected output: 1
  input.assign({4, 1, 2, 1, 2});
  cout << "s.singleNumber({4,1,2,1,2}) -> " << s.singleNumber(input)
       << '\n';  // expected output: 4

  cout << "Elapsed time: " << Solution::start_stop_timer() << " seconds\n";
  return 0;
}
