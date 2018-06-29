/*
Given a string, find the length of the longest substring without repeating
characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer
must be a substring, "pwke" is a subsequence and not a substring.
*/

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

static int sres = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

class Solution {
 public:
  size_t lengthOfLongestSubstring(string s) const {    

    if (s.empty()) 
    	return 0;

    const size_t s_len{s.length()};

    size_t max_substr_len{1};
    unordered_map<char, size_t> last_visited_unique_char_positions{};
    size_t start{}, i{};

    while (i < s_len) {
      if (s_len - start <= max_substr_len)
        return max_substr_len;

      if (last_visited_unique_char_positions.find(s[i]) !=
          end(last_visited_unique_char_positions)) {
        if (i - start > max_substr_len)
          max_substr_len = i - start;
        if (i + 1 < s_len && s[i] == s[i + 1]) {
          i++;
          while (i + 1 < s_len && s[i] == s[i + 1])
            i++;
          start = i++;
        } else {
          start = last_visited_unique_char_positions[s[i]] + 1;
          i = start + 1;
        }

        last_visited_unique_char_positions.clear();
        last_visited_unique_char_positions[s[start]] = start;
      } else {
        last_visited_unique_char_positions[s[i]] = i;
        i++;
      }
    }

    if (i - start > max_substr_len)
      max_substr_len = i - start;

    return max_substr_len;
  }
};

int main() {
  Solution s{};

  cout << "s.lengthOfLongestSubstring(string{\"abcabcbb\"}) -> "
       << s.lengthOfLongestSubstring(string{"abcabcbb"})
       << '\n';  // expected output: 3
  cout << "s.lengthOfLongestSubstring(string{\"bbbbb\"}) -> "
       << s.lengthOfLongestSubstring(string{"bbbbb"})
       << '\n';  // expected output: 1
  cout << "s.lengthOfLongestSubstring(string{\"pwwkew\"}) -> "
       << s.lengthOfLongestSubstring(string{"pwwkew"})
       << '\n';  // expected output: 3
  cout << "s.lengthOfLongestSubstring(string{\"au\"}) -> "
       << s.lengthOfLongestSubstring(string{"au"})
       << '\n';  // expected output: 2
  cout << "s.lengthOfLongestSubstring(string{\"dvdf\"}) -> "
       << s.lengthOfLongestSubstring(string{"dvdf"})
       << '\n';  // expected output: 3

  return 0;
}
