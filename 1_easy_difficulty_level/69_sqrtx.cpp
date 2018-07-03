/*
69. Leetcode coding challenge: Sqrt(x)

Implement int sqrt(int x).

Compute and return the square root of x, where x is guaranteed to be a
non-negative integer.

Since the return type is an integer, the decimal digits are truncated and only
the integer part of the result is returned.

Example 1:

Input: 4
Output: 2

Example 2:

Input: 8
Output: 2
Explanation: The square root of 8 is 2.82842..., and since
             the decimal part is truncated, 2 is returned.
*/

#include <cmath>
#include <iostream>

using namespace std;

template <typename T>
T optimal_sqrt(const T value) {
  T low{};
  T high{value};

  T next{low};

  while (++next < high) {
    T current{low + (high - low) / 2};

    const T product{current * current};

    if (value < product) {
      const T smaller_product{(current - 1) * (current - 1)};
      if (value > smaller_product)
        return current - 1;
      high = current;
    } else
      low = current;

    next = low;
  }

  if (value == low * low)
    return low;

  return -1;
}

static int sres = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

class Solution {
 public:
  uint64_t mySqrt(const uint64_t x) {
    if (!x)
      return 0;

    uint64_t low{};
    uint64_t high{x + 1};
    uint64_t next{low};

    while (++next < high) {
      uint64_t current{low + (high - low) / 2};

      const uint64_t product{current * current};

      if (x < product) {
        const uint64_t current_less{current - 1};
        const uint64_t smaller_product{current_less * current_less};
        if (x > smaller_product)
          return current_less;
        high = current;
      } else
        low = current;

      next = low;
    }

    if (x == low * low)
      return low;

    return 0;
  }
};

int main() {
  Solution s{};

  cout << "s.mySqrt(1) -> " << s.mySqrt(1) << '\n';      // expected output: 1
  cout << "s.mySqrt(4) -> " << s.mySqrt(4) << '\n';      // expected output: 2
  cout << "s.mySqrt(8) -> " << s.mySqrt(8) << '\n';      // expected output: 2
  cout << "s.mySqrt(230) -> " << s.mySqrt(230) << '\n';  // expected output: 15

  return 0;
}
