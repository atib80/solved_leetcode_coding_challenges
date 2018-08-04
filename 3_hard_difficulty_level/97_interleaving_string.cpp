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
  bool check_if_s1_and_s2_interleaved(const string& s1,
                                      const int s1_len,
                                      const string& s2,
                                      const int s2_len,
                                      const string& s3,
                                      const int s3_len,
                                      const int s1_pos,
                                      const int s2_pos,
                                      const int s1_next_s3_pos,
                                      const int s2_next_s3_pos,
                                      vector<int>& visited_s3_chars) {
    if (s1_pos == s1_len && s2_pos == -1)
      return true;

    if (s1_pos < s1_len || s2_pos >= 0) {
      int i{s1_next_s3_pos}, j{s2_next_s3_pos};
      while (i < s3_len || j >= 0) {
        if (i < s3_len) {
          const size_t next_s1_pos{s3.find(s1[s1_pos], i)};
          if (string::npos != next_s1_pos) {
            if (!visited_s3_chars[next_s1_pos]) {
              visited_s3_chars[next_s1_pos] = 1;
              if (check_if_s1_and_s2_interleaved(
                      s1, s1_len, s2, s2_len, s3, s3_len, s1_pos + 1, s2_pos,
                      next_s1_pos + 1, j, visited_s3_chars))
                return true;
              visited_s3_chars[next_s1_pos] = 0;
            }
          } else
            return false;
          i++;
        }

        if (j >= 0) {
          const size_t next_s2_pos{s3.rfind(s2[s2_pos], j)};
          if (string::npos != next_s2_pos) {
            if (!visited_s3_chars[next_s2_pos]) {
              visited_s3_chars[next_s2_pos] = 1;
              if (check_if_s1_and_s2_interleaved(
                      s1, s1_len, s2, s2_len, s3, s3_len, s1_pos, s2_pos - 1, i,
                      next_s2_pos - 1, visited_s3_chars))
                return true;
              visited_s3_chars[next_s2_pos] = 0;
            }
          } else
            return false;
          j--;
        }
      }
    }

    return false;
  }

 public:
  bool isInterleave(const string& s1, const string& s2, const string& s3) {
    size_t char_freq_s3[128]{};
    size_t char_freq_s1_s2[128]{};
    const size_t s1_len{s1.length()};
    const size_t s2_len{s2.length()};
    const size_t s3_len{s3.length()};
    if (!s1_len && !s2_len && !s3_len)
      return true;
    if ((s1_len + s2_len != s3_len) || (!s1_len && !s2_len))
      return false;
    if ((!s1_len && s2 == s3) || (!s2_len && s1 == s3))
      return true;
    const size_t min_s1_s2_len{s1_len <= s2_len ? s1_len : s2_len};
    const size_t max_s1_s2_len{s1_len > s2_len ? s1_len : s2_len};
    const string& longer_str{s1_len > s2_len ? s1 : s2};

    for (size_t i{}; i < min_s1_s2_len; i++) {
      char_freq_s1_s2[s1[i]]++;
      char_freq_s1_s2[s2[i]]++;
    }

    for (size_t i{min_s1_s2_len}; i < max_s1_s2_len; i++)
      char_freq_s1_s2[longer_str[i]]++;

    for (size_t i{}; i < s3_len; i++)
      char_freq_s3[s3[i]]++;

    for (size_t i{}; i < 128; i++)
      if (char_freq_s3[i] && char_freq_s3[i] != char_freq_s1_s2[i])
        return false;

    vector<int> visited_s3_chars(s3_len, 0);

    if (check_if_s1_and_s2_interleaved(s1, s1_len, s2, s2_len, s3, s3_len, 0,
                                       s2_len - 1, 0, s3_len - 1,
                                       visited_s3_chars))
      return true;

    return false;
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
       // << "s.isInterleave(\"cabbcaaacacbac\", \"acabaabacabcca\", "
       //    "\"cacabaabacaabccbabcaaacacbac\") -> "
       // << s.isInterleave("cabbcaaacacbac", "acabaabacabcca",
       //                   "cacabaabacaabccbabcaaacacbac")
       // << '\n'  // expected output: false
       << noboolalpha;

  return 0;
}
