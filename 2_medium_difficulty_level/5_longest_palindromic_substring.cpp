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
#include <utility>

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
    size_t i{start_index}, j{start_index + current_substr_len - 1};

    while (i < j && str[i] == str[j]) {
      ++i;
      --j;
    }

    return !(i < j);
  }

  std::string longestPalindrome(std::string str) {
    const size_t str_len{str.length()};

    if (str_len < 2U)
      return str;

    size_t current_substr_len{str_len};

    while (current_substr_len > 1U) {
      for (size_t i{}; i + current_substr_len <= str_len; ++i) {
        if (str[i] != str[i + current_substr_len - 1])
          continue;
        if (check_if_current_substring_is_palindromic(str, i,
                                                      current_substr_len)) {
          return str.substr(i, current_substr_len);
        }
      }

      --current_substr_len;
    }

    return string(1, str[0]);
  }

  static pair<int, int> get_palindromic_substring_start_and_len(
      const std::string& str,
      int i,
      int j) {
    int length{i == j ? 1 : 0};

    if (i == j) {
      --i;
      ++j;
    }

    while (i >= 0 && j < (int)str.length()) {
      if (str[i] != str[j])
        break;
      length += 2;
      --i;
      ++j;
    }

    return {i + 1, length};
  }

  std::string longestPalindrome_v2(std::string str) {
    const int str_len = str.length();

    if (str_len < 2)
      return str;

    int start_pos{}, max_substr_len{1};

    for (int i{str_len / 2 - 1}, j{str_len / 2}; i >= 0 && j < str_len;
         --i, ++j) {
      if (i > 0 && 2 * i + 1 > max_substr_len) {
        const pair<int, int> p1{
            get_palindromic_substring_start_and_len(str, i, i)};

        if (p1.second > max_substr_len) {
          start_pos = p1.first;
          max_substr_len = p1.second;
        }
      }

      if (2 * (i + 1) > max_substr_len) {
        const pair<int, int> p2{
            get_palindromic_substring_start_and_len(str, i, i + 1)};

        if (p2.second > max_substr_len) {
          start_pos = p2.first;
          max_substr_len = p2.second;
        }
      }

      if (j < str_len - 1 && 2 * (str_len - 1 - j) + 1 > max_substr_len) {
        const pair<int, int> p3{
            get_palindromic_substring_start_and_len(str, j, j)};

        if (p3.second > max_substr_len) {
          start_pos = p3.first;
          max_substr_len = p3.second;
        }
      }

      if (2 * (str_len - j) > max_substr_len) {
        const pair<int, int> p4{
            get_palindromic_substring_start_and_len(str, j - 1, j)};

        if (p4.second > max_substr_len) {
          start_pos = p4.first;
          max_substr_len = p4.second;
        }
      }
    }

    return str.substr(start_pos, max_substr_len);
  }
};

int main() {
  Solution s{};

  cout << "s.longestPalindrome_v2(\"babad\") -> "
       << s.longestPalindrome_v2("babad")
       << '\n';  // expected output: "bab" or "aba"
  cout << "s.longestPalindrome_v2(\"cbbd\") -> "
       << s.longestPalindrome_v2("cbbd") << '\n';  // expected output: "bb"

  return 0;
}
