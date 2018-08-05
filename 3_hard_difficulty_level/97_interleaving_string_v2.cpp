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
 public:
  bool isInterleave(const string& s1, const string& s2, const string& s3) {
    const size_t s1_len{s1.length()};
    const size_t s2_len{s2.length()};
    const size_t s3_len{s3.length()};

    if (s1_len + s2_len != s3_len)
      return false;
    vector<vector<int>> dp(s1_len + 1, vector<int>(s2_len + 1, 0));
    dp[0][0] = 1;

    for (size_t i{1}; i <= s2_len; i++) {
      if (s2[i - 1] == s3[i - 1])
        dp[0][i] = dp[0][i - 1];
      else
        dp[0][i] = 0;
    }
    for (size_t i{1}; i <= s1_len; i++) {
      if (s1[i - 1] == s3[i - 1])
        dp[i][0] = dp[i - 1][0];
      else
        dp[i][0] = 0;
    }
    for (size_t i{1}; i <= s1_len; i++) {
      for (size_t j{1}; j <= s2_len; j++) {
        if (s3[i + j - 1] == s1[i - 1])
          dp[i][j] = dp[i - 1][j];
        if (s3[i + j - 1] == s2[j - 1])
          dp[i][j] |= dp[i][j - 1];
      }
    }

    return static_cast<bool>(dp[s1_len][s2_len]);
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