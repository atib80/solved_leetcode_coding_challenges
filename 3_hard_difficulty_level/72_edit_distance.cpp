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

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

static int sres = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  return 0;
}();

class Solution {
  static size_t find_length_of_longest_common_subsequence(const string& word1,
                                                          const string& word2) {
    const size_t src_last{word1.length()};
    const size_t dst_last{word2.length()};

    if (!src_last)
      return dst_last;
    if (!dst_last)
      return src_last;

    if (string::npos != word1.find(word2))
      return src_last - dst_last;

    if (string::npos != word2.find(word1))
      return dst_last - src_last;

    vector<char> fixed_word1_char_indices(src_last, 0);
    fixed_word1_char_indices.reserve(src_last);
    vector<char> fixed_word2_char_indices(dst_last, 0);
    fixed_word2_char_indices.reserve(dst_last);
    vector<char> w1_char_positions(src_last, 0);
    w1_char_positions.reserve(src_last);
    vector<char> w2_char_positions(dst_last, 0);
    w2_char_positions.reserve(dst_last);

    size_t longest_common_subsequence_len{};
    size_t dst_first{};

    bool found_subseq_at_end{};

    while (dst_first < dst_last) {
      if (dst_last - dst_first <= longest_common_subsequence_len)
        break;

      w1_char_positions.clear();
      w2_char_positions.clear();

      size_t src_offset{}, dst_offset{dst_first}, seq_len{};
      ++dst_first;

      while (dst_offset < dst_last) {
        const size_t found{word1.find(word2[dst_offset], src_offset)};

        if (string::npos != found) {
          w1_char_positions[found] = word2[dst_offset];
          w2_char_positions[dst_offset] = word2[dst_offset];
          seq_len++;
          src_offset = found + 1;

        } else
          break;

        ++dst_offset;
      }

      if (seq_len > 1 && seq_len > longest_common_subsequence_len) {
        longest_common_subsequence_len = seq_len;
        if (dst_offset == dst_last)
          found_subseq_at_end = true;
        else
          found_subseq_at_end = false;
        if (longest_common_subsequence_len == dst_last)
          return src_last - dst_last;
        swap(fixed_word1_char_indices, w1_char_positions);
        swap(fixed_word2_char_indices, w2_char_positions);
      }
    }

    if (found_subseq_at_end)
      return max(dst_last - longest_common_subsequence_len,
                 src_last - longest_common_subsequence_len);

    size_t operation_count{};
    size_t src_pos{}, dst_pos{};

    while (dst_pos < dst_last && src_pos < src_last) {
      if (word2[dst_pos] == word1[src_pos]) {
        src_pos++;
        dst_pos++;
      } else {
        if (!fixed_word1_char_indices[src_pos] &&
            !fixed_word2_char_indices[dst_pos]) {
          operation_count++;
          src_pos++;
          dst_pos++;
        } else if (fixed_word1_char_indices[src_pos]) {
          operation_count++;
          dst_pos++;
        } else if (fixed_word2_char_indices[dst_pos]) {
          operation_count++;
          src_pos++;
        }
      }
    }

    operation_count += dst_last - dst_pos;
    operation_count += src_last - src_pos;

    return operation_count;
  }

 public:
  size_t minDistance(string word1, string word2) {
    return find_length_of_longest_common_subsequence(word1, word2);
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
  cout << "s.minDistance(\"azlymoka\", \"alma\") -> "
       << s.minDistance(string{"azlymoka"}, string{"alma"})
       << '\n';  // expected output: 4
  cout << "s.minDistance(\"sea\", \"ate\") -> "
       << s.minDistance(string{"sea"}, string{"ate"})
       << '\n';  // expected output: 3
  cout << "s.minDistance(\"neighbors\", \"nibozzz\") -> "
       << s.minDistance(string{"neighbors"}, string{"nibozzz"})
       << '\n';  // expected output: 6
  cout << "s.minDistance(\"park\", \"spake\") -> "
       << s.minDistance(string{"park"}, string{"spake"})
       << '\n';  // expected output: 3

  return 0;
}
