/*
567. Leetcode coding challenge: Permutation in string

Given two strings s1 and s2, write a function to return true if s2 contains the
permutation of s1. In other words, one of the first string's permutations is the
substring of the second string.

Example 1:

Input:  s1 = "ab" s2 = "eidbaooo"
Output: true
Explanation: s2 contains one permutation of s1 ("ba").

Example 2:

Input:  s1= "ab" s2 = "eidboaoo"
Output: false

Note:

    The input strings only contain lower case letters.
    The length of both given strings is in range [1, 10,000].

*/

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

class Solution {
 public:
  bool checkInclusion(string& s1, const string& s2) {
    const size_t s1_len{s1.length()};
    const size_t s2_len{s2.length()};
    if (s1_len > s2_len)
      return false;
    if (string::npos != s2.find(s1))
      return true;
    char s1_char_freq[26]{};
    char s2_char_freq[26]{};
    const size_t min_len{s1_len <= s2_len ? s1_len : s2_len};
    const size_t max_len{s1_len > s2_len ? s1_len : s2_len};
    const string& max_str{s1_len > s2_len ? s1 : s2};
    char* const max_str_char_freq{s1_len > s2_len ? s1_char_freq
                                                  : s2_char_freq};

    for (size_t i{}; i < min_len; i++) {
      s1_char_freq[s1[i] - 'a']++;
      s2_char_freq[s2[i] - 'a']++;
    }

    for (size_t i{min_len}; i < max_len; i++) {
      max_str_char_freq[max_str[i] - 'a']++;
    }

    for (size_t i{}; i < 26; i++) {
      if (s1_char_freq[i] > s2_char_freq[i])
        return false;
    }

    sort(begin(s1), end(s1));

    do {
      if (string::npos != s2.find(s1))
        return true;

    } while (next_permutation(begin(s1), end(s1)));

    return false;
  }
};

int main() {
  Solution s{};
  string s1{"ab"};
  cout << boolalpha << "s.checkInclusion(\"ab\", \"eidbaooo\") -> "
       << s.checkInclusion(s1, "eidbaooo") << '\n';  // expected output: true
  cout << "s.checkInclusion(\"ab\", \"eidboaoo\") -> "
       << s.checkInclusion(s1, "eidboaoo") << '\n';  // expected output: false
  s1 = "trinitrophenylmethylnitramine";
  cout << "s.checkInclusion(\"trinitrophenylmethylnitramine\", "
          "\"dinitrophenylhydrazinetrinitrophenylmethylnitramine\") -> "
       << s.checkInclusion(
              s1, "dinitrophenylhydrazinetrinitrophenylmethylnitramine")
       << noboolalpha << '\n';  // expected output: true

  return 0;
}
