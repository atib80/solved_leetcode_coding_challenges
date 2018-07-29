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
#include <iostream>
#include <string>

using namespace std;

static double fibonacci_numbers[21]{};

constexpr void generate_fibonacci_numbers() {
  fibonacci_numbers[0] = fibonacci_numbers[1] = 1;

  for (size_t i{2}; i < 21; i++) {
    double result = i;

    for (uint64_t j{i - 1}; j > 1; j--)
      result *= j;
    fibonacci_numbers[i] = result;
  }
}

class Solution {
  static constexpr double epsilon{1E-15};
  static double calculate_fibonacci(const size_t n) {
    double result = n;
    for (size_t i{n - 1}; i > 1; i--)
      result *= i;
    return result;
  }

 public:
  int trailingZeroes(const int n) {
    if (n < 5)
      return 0;
    double fibonacci{n < 21 ? fibonacci_numbers[n] : calculate_fibonacci(n)};
    int zero_count{};
    while (fibonacci > 10) {
      double factor{fibonacci / 10};
      if (factor - trunc(factor) < epsilon) {
        zero_count++;
        fibonacci = factor;
      } else
        break;
    }
    return zero_count;
  }
};

int main() {
  generate_fibonacci_numbers();
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
       << '\n';  // expected output: 1

  return 0;
}
