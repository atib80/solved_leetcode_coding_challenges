/*
541. Reverse string II (difficulty level: easy)

Given a string and an integer k, you need to reverse the first k characters for
every 2k characters counting from the start of the string. If there are less
than k characters left, reverse all of them. If there are less than 2k but
greater than or equal to k characters, then reverse the first k characters and
left the other as original.

Example:

Input:  s = "abcdefg", k = 2
Output: "bacdfeg"

Restrictions:

    The string consists of lower English letters only.
    Length of the given string and k will in the range [1, 10000]

*/

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class Solution {
 public:
  string reverseStr(string s, const size_t k) const {
    const size_t s_len{s.length()}, kx2{2 * k};
    if (1 == k || s_len < 2)
      return move(s);

    size_t i{};
    while (i < s_len) {
      if (i + k > s_len) {
        for (size_t m{i}, n{s_len - 1}; m < n; ++m, --n)
          swap(s[m], s[n]);
        break;
      } else if (i + kx2 > s_len) {
        for (size_t m{i}, n{i + k - 1}; m < n; ++m, --n)
          swap(s[m], s[n]);
        break;
      } else {
        for (size_t m{i}, n{i + k - 1}; m < n; ++m, --n)
          swap(s[m], s[n]);
        i += kx2;
      }
    }

    return move(s);
  }
};

int main() {
  Solution s{};

  cout << "s.reverseStr(\"abcdefg\", 2) -> "
       << s.reverseStr(string{"abcdefg"}, 2)
       << '\n';  // expected output: "bacdfeg"

  return 0;
}
