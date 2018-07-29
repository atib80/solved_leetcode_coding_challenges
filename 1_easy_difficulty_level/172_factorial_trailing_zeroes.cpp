/*
172. Leetcode coding challenge: Factorial trailing zeroes

Given an integer n, return the number of trailing zeroes in n!.

Example 1:

Input: 3
Output: 0
Explanation: 3! = 6, no trailing zero.

Example 2:

Input: 5
Output: 1
Explanation: 5! = 120, one trailing zero.

Note: Your solution should be in logarithmic time complexity.
*/

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Solution {
 public:
  int trailingZeroes(int n) {
    int zero_count{};
    while (n >= 5) {
      zero_count += n / 5;
      n /= 5;
    }
    return zero_count;
  }
};

int main() {
  Solution s{};

  cout << "s.trailingZeroes(3) -> " << s.trailingZeroes(3)
       << '\n';  // expected output: 0
  cout << "s.trailingZeroes(5) -> " << s.trailingZeroes(5)
       << '\n';  // expected output: 1
  cout << "s.trailingZeroes(6) -> " << s.trailingZeroes(6)
       << '\n';  // expected output: 1
  cout << "s.trailingZeroes(7) -> " << s.trailingZeroes(7)
       << '\n';  // expected output: 1
  cout << "s.trailingZeroes(8) -> " << s.trailingZeroes(8)
       << '\n';  // expected output: 1
  cout << "s.trailingZeroes(9) -> " << s.trailingZeroes(9)
       << '\n';  // expected output: 1
  cout << "s.trailingZeroes(10) -> " << s.trailingZeroes(10)
       << '\n';  // expected output: 2
  cout << "s.trailingZeroes(30) -> " << s.trailingZeroes(30)
       << '\n';  // expected output: 7

  return 0;
}
