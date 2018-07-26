/*
72. Leetcode coding challenge: Edit distance
(alternative solution implemented by using dynamic programming approach)

Given two words word1 and word2, find the minimum number of operations required
to convert word1 to word2.

You have the following 3 operations permitted on a word:

    Insert a character
    Delete a character
    Replace a character

Example 1:

Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation:
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')

Example 2:

Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation:
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')
*/

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

using namespace std;

class Solution {
  template <typename... Args>
  static common_type_t<Args...> min(Args&&... args) {
    const initializer_list<common_type_t<Args...>> values{
        std::forward<Args>(args)...};
    return *min_element(cbegin(values), cend(values));
  }

 public:
  size_t minDistance(const string& word1, const string& word2) {
    const size_t src_len{word1.length()};
    const size_t dst_len{word2.length()};

    if (!src_len)
      return dst_len;
    if (!dst_len)
      return src_len;

    vector<vector<int>> dp(dst_len + 1, vector<int>(src_len + 1, 0));
    for (size_t i{1}; i <= std::min(src_len, dst_len); i++) {
      dp[0][i] = i;
      dp[i][0] = i;
    }

    if (src_len > dst_len) {
      for (size_t i{std::min(src_len, dst_len)}; i <= max(src_len, dst_len);
           i++)
        dp[0][i] = i;
    } else {
      for (size_t i{std::min(src_len, dst_len)}; i <= max(src_len, dst_len);
           i++)
        dp[i][0] = i;
    }

    for (size_t i{1}; i <= dst_len; i++) {
      for (size_t j{1}; j <= src_len; j++) {
        if (word2[i - 1] == word1[j - 1])
          dp[i][j] = dp[i - 1][j - 1];
        else
          dp[i][j] =
              Solution::min(dp[i][j - 1], dp[i - 1][j - 1], dp[i - 1][j]) + 1;
      }
    }

    return dp[dst_len][src_len];
  }
};

int main() {
  Solution s{};

  cout << "s.minDistance(\"\", \"a\") -> "
       << s.minDistance("", "a") << '\n';  // expected output: 1
  cout << "s.minDistance(\"horse\", \"ros\") -> "
       << s.minDistance("horse", "ros")
       << '\n';  // expected output: 3
  cout << "s.minDistance(\"intention\", \"execution\") -> "
       << s.minDistance("intention", "execution")
       << '\n';  // expected output: 5
  cout << "s.minDistance(\"ab\", \"bc\") -> "
       << s.minDistance("ab", "bc")
       << '\n';  // expected output: 2
  cout << "s.minDistance(\"a\", \"a\") -> "
       << s.minDistance("a", "a")
       << '\n';  // expected output: 0
  cout << "s.minDistance(\"sea\", \"eat\") -> "
       << s.minDistance("sea", "eat")
       << '\n';  // expected output: 2
  cout << "s.minDistance(\"azlymoka\", \"alma\") -> "
       << s.minDistance("azlymoka", "alma")
       << '\n';  // expected output: 4
  cout << "s.minDistance(\"sea\", \"ate\") -> "
       << s.minDistance("sea", "ate")
       << '\n';  // expected output: 3
  cout << "s.minDistance(\"neighbors\", \"nibozzz\") -> "
       << s.minDistance("neighbors", "nibozzz")
       << '\n';  // expected output: 6
  cout << "s.minDistance(\"park\", \"spake\") -> "
       << s.minDistance("park", "spake")
       << '\n';  // expected output: 3
  cout << "s.minDistance(\"industry\", \"interest\") -> "
       << s.minDistance("industry", "interest")
       << '\n';  // expected output: 6
  cout << "s.minDistance(\"distance\", \"springbok\") -> "
       << s.minDistance("distance", "springbok")
       << '\n';  // expected output: 9

  return 0;
}
