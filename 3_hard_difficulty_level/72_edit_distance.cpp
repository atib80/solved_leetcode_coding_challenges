/*
72. Leetcode coding challenge: Edit distance

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

// ab, bc

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

static int sres = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  return 0;
}();

template <typename ForwardIter>
pair<typename std::iterator_traits<ForwardIter>::difference_type,
     typename std::iterator_traits<ForwardIter>::difference_type>
find_length_of_longest_common_subsequence(ForwardIter&& src_first,
                                          ForwardIter&& src_last,
                                          ForwardIter&& dst_first,
                                          ForwardIter&& dst_last) {
  using difference_type =
      typename std::iterator_traits<ForwardIter>::difference_type;

  pair<difference_type, difference_type> result{};

  if (src_first == src_last || dst_first == dst_last)
    return result;

  while (dst_first != dst_last) {
    if (distance(dst_first, dst_last) <= result.first)
      return result;

    ForwardIter src_offset{src_first}, dst_offset{dst_first};
    difference_type seq_len{};
    ++dst_first;

    while (dst_offset != dst_last) {
      auto found = find(src_offset, src_last, *dst_offset);

      if (found != src_last) {
        seq_len++;
        src_offset = ++found;
      } else
        break;

      ++dst_offset;
      if (src_offset == src_last) {
        if (seq_len > result.first)
          result.first = seq_len;
        result.second = distance(dst_offset, dst_last);
        return result;
      }
    }

    if (seq_len > result.first)
      result.first = seq_len;
  }

  return result;
}

class Solution {
 public:
  size_t minDistance(string word1, string word2) {
    const size_t word1_len{word1.length()}, word2_len{word2.length()};
    if (string::npos != word1.find(word2))
      return word1_len - word2_len;
    if (string::npos != word2.find(word1))
      return word2_len - word1_len;
    const int longer_word_len = max(word1_len, word2_len);
    const auto diff_values = find_length_of_longest_common_subsequence(
        begin(word1), end(word1), begin(word2), end(word2));
    return longer_word_len - diff_values.first + diff_values.second;
  }
};

int main() {
  Solution s{};

  cout << "s.minDistance(\"horse\", \"ros\") -> "
       << s.minDistance(string{"horse"}, string{"ros"})
       << '\n';  // expected output: 3
  cout << "s.minDistance(\"intention\", \"execution\") -> "
       << s.minDistance(string{"intention"}, string{"execution"})
       << '\n';  // expected output: 5
  cout << "s.minDistance(\"ab\", \"bc\") -> "
       << s.minDistance(string{"ab"}, string{"bc"})
       << '\n';  // expected output: 2
  cout << "s.minDistance(\"a\", \"a\") -> "
       << s.minDistance(string{"a"}, string{"a"})
       << '\n';  // expected output: 0
  cout << "s.minDistance(\"sea\", \"eat\") -> "
       << s.minDistance(string{"sea"}, string{"eat"})
       << '\n';  // expected output: 2

  return 0;
}