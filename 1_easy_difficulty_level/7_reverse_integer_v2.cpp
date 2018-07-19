/*
7. Leetcode coding challenge: Reverse integer

Given a 32-bit signed integer, reverse digits of an integer.

Example 1:

Input: 123
Output: 321

Example 2:

Input: -123
Output: -321

Example 3:

Input: 120
Output: 21

Note:
Assume we are dealing with an environment which could only store integers within
the 32-bit signed integer range: [−2^31,  2^31 − 1]. For the purpose of this
problem, assume that your function returns 0 when the reversed integer
overflows.
*/

#include <cmath>
#include <iostream>

using namespace std;

static int sres = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

constexpr static const int64_t input_min{-2147483648LL},
    input_max{2147483647LL};

class Solution {
 public:
  int reverse(int x) {
    int multiplier{1};
    if (x < 0)
      multiplier = -1;
    x = abs(x);

    int64_t output{};

    while (x) {
      output *= 10;
      output += x % 10;
      x /= 10;
    }

    output *= multiplier;

    if (output < input_min || output > input_max)
      return 0;

    return static_cast<int>(output);
  }
};

int main() {
  Solution s{};

  cout << "s.reverse(123) -> " << s.reverse(123)
       << '\n';  // expected output: 321
  cout << "s.reverse(-123) -> " << s.reverse(-123)
       << '\n';  // expected output: -321
  cout << "s.reverse(120) -> " << s.reverse(120)
       << '\n';  // expected output: 21
  cout << "s.reverse(-2147483648) -> " << s.reverse(-2147483648)
       << '\n';  // expected output: 0
  cout << "s.reverse(2147483647) -> " << s.reverse(2147483647)
       << '\n';  // expected output: 0

  return 0;
}
