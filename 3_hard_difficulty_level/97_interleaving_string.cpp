/*
97. Leetcode coding challenge: Interleaving string

Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

Example 1:

Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
Output: true

Example 2:

Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
Output: false
*/

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
  static bool isInterleaved(const char* s1, const char* s2, const char* s3) {
    if (!(*s1 || *s2 || *s3))
      return true;

    if (!(*s3))
      return false;

    return (*s3 == *s1 && isInterleaved(s1 + 1, s2, s3 + 1)) ||
           (*s3 == *s2 && isInterleaved(s1, s2 + 1, s3 + 1));
  }

 public:
  bool isInterleave(const string& s1, const string& s2, const string& s3) {
    
    return isInterleaved(s1.c_str(), s2.c_str(), s3.c_str());
  }
};

int main() {
  Solution s{};

  cout << boolalpha
       << "s.isInterleave(\"aabcc\", \"dbbca\", \"aadbbcbcac\") -> "
       << s.isInterleave("aabcc", "dbbca", "aadbbcbcac")
       << '\n'  // expected output: true
       << "s.isInterleave(\"aabcc\", \"dbbca\", \"aadbbbaccc\") -> "
       << s.isInterleave("aabcc", "dbbca", "aadbbbaccc")
       << '\n'  // expected output: false
       << "s.isInterleave(\"cabbcaaacacbac\", \"acabaabacabcca\", "
          "\"cacabaabacaabccbabcaaacacbac\") -> "
       << s.isInterleave("cabbcaaacacbac", "acabaabacabcca",
                         "cacabaabacaabccbabcaaacacbac")
       << '\n'  // expected output: false
       << noboolalpha;

  return 0;
}
