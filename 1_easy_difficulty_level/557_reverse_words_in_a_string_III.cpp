/*
557. Reverse words in a string III (difficulty level: easy)

Given a string, you need to reverse the order of characters in each word within
a sentence while still preserving whitespace and initial word order.

Example 1:

Input:  "Let's take LeetCode contest"
Output: "s'teL ekat edoCteeL tsetnoc"

Note: In the string, each word is separated by single space and there will not
be any extra space in the string.
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

using namespace std;

class Solution {
 public:
  string reverseWords(string s) const {
    const size_t s_len{s.length()};

    if (s_len < 2)
      return move(s);

    size_t i{}, word_start_pos{string::npos};

    while (true) {
      if (' ' == s[i] || '\t' == s[i] || '\n' == s[i] || s_len == i) {
        if (string::npos != word_start_pos) {
          for (size_t m{word_start_pos}, n{i - 1}; m < n; m++, n--)
            swap(s[m], s[n]);
          if (s_len == i)
            break;
          word_start_pos = string::npos;
        }

      } else if (string::npos == word_start_pos)
        word_start_pos = i;

      i++;
    }

    return move(s);
  }
};

int main() {
  Solution s{};

  cout << "s.reverseWords(\"Let's take LeetCode contest\") -> "
       << s.reverseWords(string{"Let's take LeetCode contest"})
       << '\n';  // expected output: "s'teL ekat edoCteeL tsetnoc"

  return 0;
}
