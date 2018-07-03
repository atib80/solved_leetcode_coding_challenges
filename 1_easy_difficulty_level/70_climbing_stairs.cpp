/*
70. Leetcode coding challenge: Climbing stairs

You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you
climb to the top?

Note: Given n will be a positive integer.

Example 1:

Input: 2
Output: 2
Explanation: There are two ways to climb to the top.
1. 1 step + 1 step
2. 2 steps

Example 2:

Input: 3
Output: 3
Explanation: There are three ways to climb to the top.
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step
*/

#include <iostream>
#include <unordered_map>

using namespace std;

static int sres = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

class Solution {
  unordered_map<uint64_t, uint64_t> precalculated_steps_count{};

  void find_number_of_combinations(const uint64_t number_of_stairs,
                                   uint64_t& combinations,
                                   const uint64_t current_steps_count = 0) {
    if (number_of_stairs == current_steps_count) {
      combinations++;
      return;
    }

    precalculated_steps_count[current_steps_count]++;

    if (current_steps_count < number_of_stairs)
      find_number_of_combinations(number_of_stairs, combinations,
                                  current_steps_count + 1);

    if (current_steps_count < number_of_stairs - 1)
      find_number_of_combinations(number_of_stairs, combinations,
                                  current_steps_count + 2);
  }

 public:
  Solution() = default;

  uint64_t climbingStairs(const uint64_t number_of_stairs) {
    if (precalculated_steps_count.find(number_of_stairs) !=
        end(precalculated_steps_count))
      return precalculated_steps_count.at(number_of_stairs);
    uint64_t combinations{};
    find_number_of_combinations(number_of_stairs, combinations);
    precalculated_steps_count[number_of_stairs] = combinations;
    return combinations;
  }
};

int main() {
  Solution s{};

  cout << "s.climbingStairs(10) -> " << s.climbingStairs(10)
       << '\n';  // expected output: 89
  cout << "s.climbingStairs(1) -> " << s.climbingStairs(1)
       << '\n';  // expected output: 1
  cout << "s.climbingStairs(2) -> " << s.climbingStairs(2)
       << '\n';  // expected output: 2
  cout << "s.climbingStairs(3) -> " << s.climbingStairs(3)
       << '\n';  // expected output: 3
  cout << "s.climbingStairs(4) -> " << s.climbingStairs(4)
       << '\n';  // expected output: 5
  cout << "s.climbingStairs(5) -> " << s.climbingStairs(5)
       << '\n';  // expected output: 8
  cout << "s.climbingStairs(6) -> " << s.climbingStairs(6)
       << '\n';  // expected output: 13
  cout << "s.climbingStairs(7) -> " << s.climbingStairs(7)
       << '\n';  // expected output: 21
  cout << "s.climbingStairs(8) -> " << s.climbingStairs(8)
       << '\n';  // expected output: 34
  cout << "s.climbingStairs(9) -> " << s.climbingStairs(9)
       << '\n';  // expected output: 55

  return 0;
}
