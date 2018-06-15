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
#include <iostream>

using std::abs;
using std::cout;

class Solution {
 public:
  double myPow(double x, int n) {
    if (!n)
      return 1;
    if (1 == n)
      return x;
    if (-1 == n)
      return 1 / x;
    if (1.0 == x)
      return 1.0;
    if (-1.0 == x)
      return n % 2 ? -1.0 : 1.0;
    if (INT_MIN == n && abs(x) > 1.0)
      return 0;
    if (abs(x) < 0.001 && n > 1000)
      return 0;
    const bool is_negative_exp{n < 0};
    if (INT_MIN == n)
      n++;
    n = abs(n);

    double result{x};
    for (int exp{2}; exp <= n; exp++)
      result *= x;

    return !is_negative_exp ? result : 1 / result;
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
