/*
Implement pow(x, n), which calculates x raised to the power n (xn).

Example 1:

Input: 2.00000, 10
Output: 1024.00000

Example 2:

Input: 2.10000, 3
Output: 9.26100

Example 3:

Input: 2.00000, -2
Output: 0.25000
Explanation: 2-2 = 1/22 = 1/4 = 0.25

Note:

    -100.0 < x < 100.0
    n is a 32-bit signed integer, within the range [−231, 231 − 1]
*/

#include <cmath>
#include <cstdint>
#include <iostream>

using namespace std;

static int sres = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

class Solution {
 public:
  double myPow(double x, int n) {
    const bool is_negative{n < 0};
    if (!x)
      return 0;
    if (!n)
      return 1;
    int64_t abs_n{abs(static_cast<int64_t>(n))};
    double result{1};
    for (size_t i{}; i < 32u; i++) {
      if (abs_n & 1)
        result *= x;
      abs_n >>= 1;
      x *= x;
    }

    return is_negative ? 1 / result : result;
  }
};

int main() {
  Solution s{};

  cout << "s.myPow(2.00000, 10) -> " << s.myPow(2.00000, 10)
       << '\n';  // expected output: 1024.00000
  cout << "s.myPow(2.10000, 3) -> " << s.myPow(2.10000, 3)
       << '\n';  // expected output: 9.26100
  cout << "s.myPow(2.00000, -2) -> " << s.myPow(2.00000, -2)
       << '\n';  // expected output: 0.25000
  cout << "s.myPow(0.00001, 2147483647) -> " << s.myPow(0.00001, 2147483647)
       << '\n';  // expected output: 0.0

  return 0;
}
