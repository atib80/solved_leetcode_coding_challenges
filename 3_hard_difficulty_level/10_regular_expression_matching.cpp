/*
10. Leetcode coding challenge: Regular expression matching

Given an input string (s) and a pattern (p), implement regular expression
matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

Note:

    s could be empty and contains only lowercase letters a-z.
    p could be empty and contains only lowercase letters a-z, and characters
like . or *.

Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".

Example 2:

Input:
s = "aa"
p = "a*"
Output: true
Explanation: '*' means zero or more of the precedeng element, 'a'. Therefore, by
repeating 'a' once, it becomes "aa".

Example 3:

Input:
s = "ab"
p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".

Example 4:

Input:
s = "aab"
p = "c*a*b"
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore it
matches "aab".

Example 5:

Input:
s = "mississippi"
p = "mis*is*p*."
Output: false
*/

#include <iomanip>
#include <iostream>

using namespace std;

class Solution {
  static bool match(const char* s, const char* p) {
    while (*s && *p) {
      if (*(p + 1) == '*') {
        return match(s, p + 2) || (*s == *p || *p == '.') && match(s + 1, p);
      } else if (*s == *p || *p == '.') {
        ++s;
        ++p;
      } else
        return false;
    }

    while (*p && *(p + 1) == '*')
      p += 2;
    return !*s && !*p;
  }

 public:
  bool isMatch(const string& s, const string& p) {
    return match(s.c_str(), p.c_str());
  }
};

int main() {
  Solution s{};

  cout << boolalpha << "s.isMatch(\"aa\", \"a\") -> " << s.isMatch("aa", "a")
       << '\n'  // expected output: false
       << "s.isMatch(\"aa\", \"a*\") -> " << s.isMatch("aa", "a*")
       << '\n'  // expected output: true
       << "s.isMatch(\"ab\", \".*\") -> " << s.isMatch("ab", ".*")
       << '\n'  // expected output: true
       << "s.isMatch(\"aab\", \"c*a*b\") -> " << s.isMatch("aab", "c*a*b")
       << '\n'  // expected output: true
       << "s.isMatch(\"mississippi\", \"mis*is*p*.\") -> "
       << s.isMatch("mississippi", "mis*is*p*.") << noboolalpha
       << '\n';  // expected output: false

  return 0;
}
