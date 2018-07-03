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

#include <iomanip>
#include <iostream>

using namespace std;

class Solution {
  static inline double fibonacci_numbers[93];

  static constexpr void initialize_fib_series(const size_t fib_level) {
    for (size_t i{}; i < fib_level; i++)
      fibonacci_numbers[i] = fibonacci(i);
  }

  static constexpr double fibonacci(const size_t fib_level) {
    double first{1}, second{1};

    for (size_t i{}; i < fib_level; i++) {
      const double temp{second};
      second += first;
      first = temp;
    }

    return first;
  }

  static double calculate_fibonacci(const uint64_t fib_level) {
    if (fib_level < 2)
      return 1;

    double first{1}, second{1};

    for (uint64_t i{}; i < fib_level; i++) {
      const double temp{second};
      second += first;
      first = temp;
    }

    return first;
  }

 public:
  Solution() { initialize_fib_series(93); }
  double climbStairs(const uint64_t number_of_stairs) {
    if (number_of_stairs > 92)
      return calculate_fibonacci(number_of_stairs);
    return fibonacci_numbers[number_of_stairs];
  }
};

int main() {
  Solution s{};
  cout << fixed << setprecision(0) << "s.climbStairs(10) -> "
       << s.climbStairs(10) << '\n'  // expected output: 89
       << "s.climbStairs(1) -> " << s.climbStairs(1)
       << '\n'  // expected output: 1
       << "s.climbStairs(2) -> " << s.climbStairs(2)
       << '\n'  // expected output: 2
       << "s.climbStairs(3) -> " << s.climbStairs(3)
       << '\n'  // expected output: 3
       << "s.climbStairs(4) -> " << s.climbStairs(4)
       << '\n'  // expected output: 5
       << "s.climbStairs(5) -> " << s.climbStairs(5)
       << '\n'  // expected output: 8
       << "s.climbStairs(6) -> " << s.climbStairs(6)
       << '\n'  // expected output: 13
       << "s.climbStairs(7) -> " << s.climbStairs(7)
       << '\n'  // expected output: 21
       << "s.climbStairs(8) -> " << s.climbStairs(8)
       << '\n'  // expected output: 34
       << "s.climbStairs(9) -> " << s.climbStairs(9)
       << '\n'  // expected output: 55
       << "s.climbStairs(90) -> " << s.climbStairs(90) << '\n'
       << "s.climbStairs(91) -> " << s.climbStairs(91) << '\n'
       << "s.climbStairs(92) -> " << s.climbStairs(92) << '\n'
       << "s.climbStairs(93) -> " << s.climbStairs(93) << '\n';

  return 0;
}
