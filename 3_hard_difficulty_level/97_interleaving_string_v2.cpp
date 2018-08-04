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
  static bool helper(const string& s1,
                     const string& s2,
                     const string& s3,
                     const size_t m,
                     const size_t n,
                     const size_t len) {
    if (m + n != len)
      return false;
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    dp[0][0] = true;

    for (size_t i{1}; i <= n; i++) {
      if (s2[i - 1] == s3[i - 1])
        dp[0][i] = dp[0][i - 1];
      else
        dp[0][i] = false;
    }
    for (size_t i{1}; i <= m; i++) {
      if (s1[i - 1] == s3[i - 1])
        dp[i][0] = dp[i - 1][0];
      else
        dp[i][0] = false;
    }
    for (size_t i{1}; i <= m; i++) {
      for (size_t j{1}; j <= n; j++) {
        if (s3[i + j - 1] == s1[i - 1])
          dp[i][j] = dp[i - 1][j];
        if (s3[i + j - 1] == s2[j - 1])
          dp[i][j] = dp[i][j] | dp[i][j - 1];
      }
    }

    return dp[m][n];
  }

 public:
  bool isInterleave(const string& s1, const string& s2, const string& s3) {
    return helper(s1, s2, s3, s1.length(), s2.length(), s3.length());
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