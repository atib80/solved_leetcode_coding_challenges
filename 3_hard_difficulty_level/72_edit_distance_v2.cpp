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
#include <queue>
#include <string>

using namespace std;

static int sres = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  return 0;
}();

struct op_state {
  size_t src_index;
  size_t dst_index;
  size_t op_count;

  explicit op_state(const size_t src_index,
                    const size_t dst_index,
                    const size_t op_count)
      : src_index{src_index}, dst_index{dst_index}, op_count{op_count} {}
};

class Solution {
  static size_t find_minimum_edit_distance(const string& word1,
                                           const string& word2) {
    const size_t src_len{word1.length()};
    const size_t dst_len{word2.length()};

    if (!src_len)
      return dst_len;
    if (!dst_len)
      return src_len;

    if (string::npos != word1.find(word2))
      return src_len - dst_len;

    if (string::npos != word2.find(word1))
      return dst_len - src_len;

    size_t min_operation_count{string::npos};

    queue<op_state> q{{op_state{0, 0, 0}}};

    while (!q.empty()) {
      op_state current_op{move(q.front())};
      q.pop();

      if (current_op.op_count >= min_operation_count)
        continue;

      if (src_len == current_op.src_index) {
        const size_t current_op_count{current_op.op_count + dst_len -
                                      current_op.dst_index};
        if (current_op_count < min_operation_count)
          min_operation_count = current_op_count;
        continue;
      }

      if (dst_len == current_op.dst_index) {
        const size_t current_op_count{current_op.op_count + src_len -
                                      current_op.src_index};
        if (current_op_count < min_operation_count)
          min_operation_count = current_op_count;
        continue;
      }

      if (word1[current_op.src_index] == word2[current_op.dst_index]) {
        current_op.src_index++;
        current_op.dst_index++;
        q.emplace(move(current_op));
        continue;
      }

      q.emplace(current_op.src_index + 1, current_op.dst_index + 1,
                current_op.op_count + 1);
      q.emplace(current_op.src_index, current_op.dst_index + 1,
                current_op.op_count + 1);
      current_op.src_index++;
      current_op.op_count++;
      q.emplace(move(current_op));
    }

    return min_operation_count;
  }

 public:
  size_t minDistance(string word1, string word2) {
    return find_minimum_edit_distance(word1, word2);
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
  cout << "s.minDistance(\"industry\", \"interest\") -> "
       << s.minDistance(string{"industry"}, string{"interest"})
       << '\n';  // expected output: 6

  return 0;
}
