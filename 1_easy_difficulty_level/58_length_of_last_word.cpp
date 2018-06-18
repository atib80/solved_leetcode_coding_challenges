/*
58. Leetcode coding challenge: Length of Last Word

Given a string s consists of upper/lower-case alphabets and empty space
characters ' ', return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters
only.

Example:

Input:  "Hello World"
Output: 5
*/

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

static int sres = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

class Solution {
 public:
  size_t lengthOfLastWord(string s) {
    const size_t s_len{s.length()};
    if (!s_len)
      return 0;
    if (all_of(begin(s), end(s), [](const char ch) { return ' ' == ch; }))
      return 0;
    const size_t last_space_char_pos{s.rfind(' ')};
    if (last_space_char_pos == s_len - 1) {
      int last = last_space_char_pos - 1;
      while (' ' == s[last] && last > 0)
        last--;
      int start{last};
      while (' ' != s[start] && start > 0)
        start--;
      if (' ' == s[start])
        start++;
      return last - start + 1;
    }
    if (string::npos == last_space_char_pos)
      return s_len;
    return s_len - (last_space_char_pos + 1);
  }
};

int main() {
  Solution s{};

  cout << "s.lengthOfLastWord(\"Hello World\") -> "
       << s.lengthOfLastWord(string{"Hello World"})
       << '\n';  // expected output: 5

  return 0;
}