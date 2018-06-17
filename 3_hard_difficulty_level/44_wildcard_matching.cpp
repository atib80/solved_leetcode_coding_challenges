/*
Given an input string (s) and a pattern (p), implement wildcard pattern matching
with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

Note:

    s could be empty and contains only lowercase letters a-z.
    p could be empty and contains only lowercase letters a-z, and characters
like ? or *.

Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".

Example 2:

Input:
s = "aa"
p = "*"
Output: true
Explanation: '*' matches any sequence.

Example 3:

Input:
s = "cb"
p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match
'b'.

Example 4:

Input:
s = "adceb"
p = "*a*b"
Output: true
Explanation: The first '*' matches the empty sequence, while the second '*'
matches the substring "dce".

Example 5:

Input:
s = "acdcb"
p = "a*c?b"
Output: false
*/

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

static int sres = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  return 0;
}();

using std::cout;
using std::string;
using std::vector;

class Solution {
 public:
  bool isMatch(string s, string p) {
    const size_t s_len{s.length()};
    const size_t p_len{p.length()};

    vector<vector<int>> s_by_p(s_len + 1, vector<int>(p_len + 1));
    s_by_p[0][0] = 1;

    for (size_t j{}; j < p_len; j++) {
      if ('*' == p[j])
        s_by_p[0][j + 1] = 1;
      else
        break;
    }

    for (size_t i{1}; i <= s_len; i++) {
      for (size_t j{1}; j <= p_len; j++) {
        if (s[i - 1] == p[j - 1] || '?' == p[j - 1])
          s_by_p[i][j] = s_by_p[i - 1][j - 1];
        else if ('*' == p[j - 1])
          s_by_p[i][j] = s_by_p[i][j - 1] || s_by_p[i - 1][j];
      }
    }

    return s_by_p.back().back();
  }
};

int main() {
  Solution s{};

  cout << std::boolalpha;
  cout << "s.isMatch(string{\"aa\"}, string{\"a\"}) -> "
       << s.isMatch(string{"aa"}, string{"a"})
       << '\n';  // expected output: false
  cout << "s.isMatch(string{\"aa\"}, string{\"*\"}) -> "
       << s.isMatch(string{"aa"}, string{"*"})
       << '\n';  // expected output: true
  cout << "s.isMatch(string{\"cb\"}, string{\"?a\"}) -> "
       << s.isMatch(string{"cb"}, string{"?a"})
       << '\n';  // expected output: false
  cout << "s.isMatch(string{\"adceb\"}, string{\"*a*b\"}) -> "
       << s.isMatch(string{"adceb"}, string{"*a*b"})
       << '\n';  // expected output: true
  cout << "s.isMatch(string{\"acdcb\"}, string{\"a*c?b\"}) -> "
       << s.isMatch(string{"acdcb"}, string{"a*c?b"})
       << '\n';  // expected output: false
  cout << std::noboolalpha;

  return 0;
}
