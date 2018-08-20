/*
115. Leetcode coding challenge: Distinct subsequences

Given a string S and a string T, count the number of distinct subsequences of S
which equals T.

A subsequence of a string is a new string which is formed from the original
string by deleting some (can be none) of the characters without disturbing the
relative positions of the remaining characters. (ie, "ACE" is a subsequence of
"ABCDE" while "AEC" is not).

Example 1:

Input: S = "rabbbit", T = "rabbit"
Output: 3
Explanation:

As shown below, there are 3 ways you can generate "rabbit" from S.
(The caret symbol ^ means the chosen letters)

rabbbit
^^^^ ^^
rabbbit
^^ ^^^^
rabbbit
^^^ ^^^

Example 2:

Input: S = "babgbag", T = "bag"
Output: 5
Explanation:

As shown below, there are 5 ways you can generate "bag" from S.
(The caret symbol ^ means the chosen letters)

babgbag
^^ ^
babgbag
^^    ^
babgbag
^    ^^
babgbag
  ^  ^^
babgbag
    ^^^
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
  const char* s_ptr;
  const char* t_ptr;
  size_t s_len;
  size_t t_len;
  size_t distinct_subsequences;

  void construct_needle_from_characters_of_s(const size_t s_pos,
                                             const size_t t_pos) {
    if (t_pos == t_len) {
      distinct_subsequences++;
      return;
    }

    if (s_pos > s_len - (t_len - t_pos))
      return;

    for (size_t i{s_pos}; i < s_len; i++) {
      if (s_ptr[i] == t_ptr[t_pos])
        construct_needle_from_characters_of_s(i + 1, t_pos + 1);
    }
  }

 public:
  int numDistinct(const string& s, const string& t) {
    s_ptr = s.c_str();
    t_ptr = t.c_str();
    s_len = s.length();
    t_len = t.length();
    distinct_subsequences = 0;
    construct_needle_from_characters_of_s(0, 0);
    return distinct_subsequences;
  }
};

int main() {
  Solution s{};

  cout << "s.numDistinct(\"rabbbit\", \"rabbit\") -> "
       << s.numDistinct("rabbbit", "rabbit") << '\n';  // expected output: 3
  cout << "s.numDistinct(\"babgbag\", \"bag\") -> "
       << s.numDistinct("babgbag", "bag") << '\n';  // expected output: 5

  return 0;
}
