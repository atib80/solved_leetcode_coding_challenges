/*
Leetcode coding challenge: Count and say
(simple iterative solution using some elements of dynamic programming as well)

The count-and-say sequence is the sequence of integers with the first five terms
as following:

1.     1
2.     11
3.     21
4.     1211
5.     111221

1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.

Given an integer n, generate the nth term of the count-and-say sequence.

Note: Each term of the sequence of integers will be represented as a string.

Example 1:

Input: 1
Output: "1"

Example 2:

Input: 4
Output: "1211"
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <string>

using std::begin;
using std::cout;
using std::end;
using std::map;
using std::string;
using std::upper_bound;

class Solution {
 public:
  string countAndSay(const int n) {
    static map<int, string> precalculated_count_and_say_sequences{
        {1, "1"}, {2, "11"}, {3, "21"}, {4, "1211"}, {5, "111221"}};

    if (end(precalculated_count_and_say_sequences) !=
        precalculated_count_and_say_sequences.find(n))
      return precalculated_count_and_say_sequences.at(n);

    auto ub_iter = precalculated_count_and_say_sequences.upper_bound(n);

    if (ub_iter == end(precalculated_count_and_say_sequences) &&
        !precalculated_count_and_say_sequences.empty())
      --ub_iter;

    string current_sequence{
        ub_iter != end(precalculated_count_and_say_sequences) ? ub_iter->second
                                                              : "1"};
    int i{ub_iter != end(precalculated_count_and_say_sequences)
              ? ub_iter->first + 1
              : 2};

    string next_sequence{};
    next_sequence.reserve(4096);

    string num_str{};
    num_str.reserve(16);

    for (; i <= n; i++) {
      const size_t current_sequence_len{current_sequence.length()};

      for (size_t j{}; j < current_sequence_len; j++) {
        size_t count{1};

        while (j < current_sequence_len - 1 &&
               current_sequence[j] == current_sequence[j + 1]) {
          count++;
          j++;
        }

        num_str.clear();
        while (count) {
          num_str.insert(0, 1, count % 10 + '0');
          count /= 10;
        }

        next_sequence.append(num_str);
        next_sequence.push_back(current_sequence[j]);
      }

      swap(current_sequence, next_sequence);
      next_sequence.clear();
    }

    precalculated_count_and_say_sequences[n] = current_sequence;

    return current_sequence;
  }
};

int main() {
  Solution s{};
  cout << s.countAndSay(1) << '\n';  // expected output: "1"
  cout << s.countAndSay(2) << '\n';  // expected output: "11"
  cout << s.countAndSay(3) << '\n';  // expected output: "21"
  cout << s.countAndSay(4) << '\n';  // expected output: "1211"
  cout << s.countAndSay(5) << '\n';  // expected output: "111221"
  cout << s.countAndSay(6) << '\n';  // expected output: "312211"
  cout << s.countAndSay(7) << '\n';  // expected output: "13112221"
  cout << s.countAndSay(8) << '\n';  // expected output: "1113213211"
  cout << s.countAndSay(9) << '\n';  // expected output: "31131211131221"
  cout << s.countAndSay(10) << '\n'; // expected output: "13211311123113112211"

  return 0;
}