/*
91. Leetcode coding challenge: Decode ways

A message containing letters from A-Z is being encoded to numbers using the
following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26

Given a non-empty string containing only digits, determine the total number of
ways to decode it.

Example 1:

Input: "12"
Output: 2
Explanation: It could be decoded as "AB" (1 2) or "L" (12).

Example 2:

Input: "226"
Output: 3
Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
*/

#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
 public:
  size_t numDecodings(const string& s) {
    const size_t s_len{s.length()};
    queue<size_t> q{{0u}};
    size_t count{};

    if ('0' == s.front())
      return 0;

    if (s_len > 1) {
      bool found{true};

      for (size_t i{}; i < s_len - 1; i += 2) {
        if ('1' == s[i] && '0' == s[i + 1])
          continue;
        found = false;
        break;
      }

      if (found)
        return 1;
    }

    while (!q.empty()) {
      size_t pos{q.front()};
      q.pop();

      if (pos >= s_len) {
        count++;
        continue;
      }

      if ('0' == s[pos])
        continue;

      if (pos + 1 <= s_len)
        q.emplace(pos + 1);

      if (pos + 2 <= s_len) {
        const size_t ascii{static_cast<size_t>(s[pos] - '0') * 10 +
                           static_cast<size_t>(s[pos + 1] - '0')};
        if (ascii >= 10 && ascii <= 26)
          q.emplace(pos + 2);
      }
    }

    return count;
  }
};

int main() {
  Solution s{};

  cout << "s.numDecodings(\"12\") -> " << s.numDecodings("12")
       << '\n';  // expected output: 2
  cout << "s.numDecodings(\"226\") -> " << s.numDecodings("226")
       << '\n';  // expected output: 3
  cout << "s.numDecodings(\"01\") -> " << s.numDecodings("01")
       << '\n';  // expected output: 0
  cout << "s.numDecodings(\"10\") -> " << s.numDecodings("10")
       << '\n';  // expected output: 1
  cout << "s.numDecodings(\"010\") -> " << s.numDecodings("010")
       << '\n';  // expected output: 0
  cout << "s.numDecodings(\"1010\") -> " << s.numDecodings("1010")
       << '\n';  // expected output: 1
  cout << "s.numDecodings(\"1224\") -> " << s.numDecodings("1224")
       << '\n';  // expected output: 5

  const string large_input{
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "101010101010101010101010101010101010101010101010101010101010101010101010"
      "10101010101010101010101010101010101010101010101010101010101010101010101"
      "0"};
  cout << "s.numDecodings("
          "\"101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010101010101010101010"
          "10101010101010101010101010101010101010101010101010\") -> "
       << s.numDecodings(large_input) << '\n';  // expected output: 1

  return 0;
}
