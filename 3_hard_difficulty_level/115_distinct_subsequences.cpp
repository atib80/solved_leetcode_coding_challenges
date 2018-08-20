/*
115. Leetcode coding challenge: Distinct subsequences
(solution implemented by using dynamic programming approach)

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
 public:
  int numDistinct(const string& s, const string& t) {
    const size_t s_len{s.length()};
    const size_t t_len{t.length()};
    if (!s_len || !t_len)
      return 0;
    vector<int> dp(t_len + 1, 0);
    dp[0] = 1;

    for (size_t i{}; i < s_len; i++) {
      for (size_t j{t_len}; j >= 1; j--) {
        if (s[i] == t[j - 1])
          dp[j] = dp[j] + dp[j - 1];
      }
    }

    return dp[t_len];
  }
};

int main() {
  Solution s{};

  cout << "s.numDistinct(\"rabbbit\", \"rabbit\") -> "
       << s.numDistinct("rabbbit", "rabbit") << '\n';  // expected output: 3
  cout << "s.numDistinct(\"babgbag\", \"bag\") -> "
       << s.numDistinct("babgbag", "bag") << '\n';  // expected output: 5

  cout << "s.numDistinct("
          "\"adbdadeecadeadeccaeaabdabdbcdabddddabcaaadbabaaedeeddeaeebcdeabcaa"
          "aeeaeeabcddcebddebeebedaecccbdcbcedbdaeaedcdebeecdaaedaacadbdccabdda"
          "ddacdddc\", \"bcddceeeebecbc\") -> "
       << s.numDistinct(
              "adbdadeecadeadeccaeaabdabdbcdabddddabcaaadbabaaedeeddeaeebcdeabc"
              "aaaeeaeeabcddcebddebeebedaecccbdcbcedbdaeaedcdebeecdaaedaacadbdc"
              "cabddaddacdddc",
              "bcddceeeebecbc")
       << '\n';  // expected output: 5

  return 0;
}
