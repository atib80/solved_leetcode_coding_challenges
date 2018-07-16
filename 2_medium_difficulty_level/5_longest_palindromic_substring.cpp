/*
5. Leetcode coding challenge: Longest palindromic substring

Given a string s, find the longest palindromic substring in s. You may assume
that the maximum length of s is 1000.

Example 1:

Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.

Example 2:

Input: "cbbd"
Output: "bb"
*/

#include <iostream>
#include <string>

using namespace std;

static int sr = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

class Solution {
 public:
  static bool check_if_current_substring_is_palindromic(
      const std::string& str,
      const size_t start_index,
      const size_t current_substr_len) {
    for (size_t i{start_index}, j{start_index + current_substr_len - 1}; i < j;
         i++, j--) {
      if (str[i] != str[j])
        return false;
    }

    return true;
  }

  std::string longestPalindrome(std::string str) {
    const size_t str_len{str.length()};

    if (str_len < 2)
      return str;

    size_t current_substr_len{str_len};

    while (current_substr_len > 1) {
      for (size_t i{}; i + current_substr_len <= str_len; i++) {
        if (str[i] != str[i + current_substr_len - 1]) continue;
        if (check_if_current_substring_is_palindromic(str, i,
                                                      current_substr_len)) {
          return str.substr(i, current_substr_len);
        }
      }

      current_substr_len--;
    }

    return string(1, str[0]);
  }
};

int main() {
  Solution s{};

  cout << "s.longestPalindrome(\"babad\") -> "
       << s.longestPalindrome(string{"babad"})
       << '\n';  // expected output: "bab" or "aba"
  cout << "s.longestPalindrome(\"cbbd\") -> "
       << s.longestPalindrome(string{"cbbd"}) << '\n';  // expected output: "bb"

  return 0;
}
