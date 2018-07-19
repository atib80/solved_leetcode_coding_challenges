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

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

static int sres = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

class Solution {
 public:
  int reverse(const int x) {
    std::string num_str{std::to_string(x)};

    size_t num_str_len{num_str.length()};

    if (1 == num_str_len)
      return x;

    size_t num_start{'-' == num_str[0] ? 1u : 0u};

    std::reverse(std::begin(num_str) + num_start, std::end(num_str));

    while ('0' == num_str[num_start] && num_str.length() > 1) {
      num_str.erase(num_start, 1);
    }

    int result{};

    try {
      result = std::stoi(num_str);
    } catch (std::out_of_range&) {
      return 0;
    }

    return result;
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
