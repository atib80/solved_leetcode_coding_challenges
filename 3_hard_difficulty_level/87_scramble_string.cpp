/*
Given a string s1, we may represent it as a binary tree by partitioning it to
two non-empty substrings recursively.

Below is one possible representation of s1 = "great":

    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t

To scramble the string, we may choose any non-leaf node and swap its two
children.

For example, if we choose the node "gr" and swap its two children, it produces a
scrambled string "rgeat".

    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t

We say that "rgeat" is a scrambled string of "great".

Similarly, if we continue to swap the children of nodes "eat" and "at", it
produces a scrambled string "rgtae".

    rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a

We say that "rgtae" is a scrambled string of "great".

Given two strings s1 and s2 of the same length, determine if s2 is a scrambled
string of s1.

Example 1:

Input: s1 = "great", s2 = "rgeat"
Output: true

Example 2:

Input: s1 = "abcde", s2 = "caebd"
Output: false
*/

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

class Solution {
 public:
  bool isScramble(const string& s1, const string& s2) {
    const size_t s1_len{s1.size()};
    const size_t s2_len{s2.size()};

    if (s1_len != s2_len)
      return false;
    if (s1 == s2)
      return true;

    int char_freq[256u]{};

    for (size_t i{}; i < s1_len; ++i) {
      char_freq[s1[i]]++;
      char_freq[s2[i]]--;
    }

    for (size_t i{}; i < 256u; ++i)
      if (char_freq[i])
        return false;

    for (size_t i{1}; i < s1_len; ++i) {
      const string s11{s1.substr(0, i)};
      string s21{s2.substr(0, i)};
      const string s12{s1.substr(i)};
      string s22{s2.substr(i)};

      if (isScramble(s11, s21) && isScramble(s12, s22))
        return true;

      s22 = s2.substr(0, s1_len - i);
      s21 = s2.substr(s1_len - i);
      if (isScramble(s11, s21) && isScramble(s12, s22))
        return true;
    }

    return false;
  }
};

int main() {
  Solution s{};

  cout << boolalpha << "s.isScramble(\"great\", \"rgeat\" ) -> "
       << s.isScramble(string{"great"}, string{"rgeat"})
       << '\n';  // expected output: true
  cout << "s.isScramble(\"abcde\", \"caebd\" ) -> "
       << s.isScramble(string{"abcde"}, string{"caebd"})
       << '\n';  // expected output: false

  return 0;
}
