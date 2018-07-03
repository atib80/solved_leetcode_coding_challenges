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

#include <cassert>
#include <iostream>
#include <unordered_map>

using namespace std;

static int sres = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

template <uint64_t fib_level>
struct Fib {
  static inline const double value =
      Fib<fib_level - 1>::value + Fib<fib_level - 2>::value;

  static inline double getValue(const uint64_t i) {
    if (i == fib_level)
      return value;
    else
      return Fib<fib_level - 1>::getValue(i);
  }
};

template <>
struct Fib<0> {
  static inline const double value{1};

  static inline double getValue(const uint64_t) { return 1; }
};

template <>
struct Fib<1> {
  static inline const double value{1};

  static inline double getValue(const uint64_t i) {
    if (i == 1)
      return value;
    else
      return Fib<0>::getValue(i);
  }
};

class Solution {
 public:
  Solution() = default;

  double climbStairs(const uint64_t number_of_stairs) {
    static Fib<93> fib_series{};
    return fib_series.getValue(number_of_stairs);
  }
};

int main() {
  Solution s{};

  cout << "s.climbStairs(10) -> " << s.climbStairs(10)
       << '\n';  // expected output: 89
  cout << "s.climbStairs(1) -> " << s.climbStairs(1)
       << '\n';  // expected output: 1
  cout << "s.climbStairs(2) -> " << s.climbStairs(2)
       << '\n';  // expected output: 2
  cout << "s.climbStairs(3) -> " << s.climbStairs(3)
       << '\n';  // expected output: 3
  cout << "s.climbStairs(4) -> " << s.climbStairs(4)
       << '\n';  // expected output: 5
  cout << "s.climbStairs(5) -> " << s.climbStairs(5)
       << '\n';  // expected output: 8
  cout << "s.climbStairs(6) -> " << s.climbStairs(6)
       << '\n';  // expected output: 13
  cout << "s.climbStairs(7) -> " << s.climbStairs(7)
       << '\n';  // expected output: 21
  cout << "s.climbStairs(8) -> " << s.climbStairs(8)
       << '\n';  // expected output: 34
  cout << "s.climbStairs(9) -> " << s.climbStairs(9)
       << '\n';  // expected output: 55
  cout << "s.climbStairs(90) -> " << s.climbStairs(90)
       << '\n';  // expected output: 89
  cout << "s.climbStairs(91) -> " << s.climbStairs(91)
       << '\n';  // expected output: 89
  cout << "s.climbStairs(92) -> " << s.climbStairs(92)
       << '\n';  // expected output: 89
  cout << "s.climbStairs(93) -> " << s.climbStairs(93)
       << '\n';  // expected output: 89

  return 0;
}
