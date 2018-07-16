/*
6. Leetcode coding challenge: Zigzag conversion

The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of
rows like this: (you may want to display this pattern in a fixed font for better
legibility)

P   A   H   N
A P L S I I G
Y   I   R

And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number
of rows:

string convert(string s, int numRows);

Example 1:

Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"

Example 2:

Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:

P     I    N
A   L S  I G
Y A   H R
P     I
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

static int sr = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

class Solution {
 public:
  string convert(string s, const size_t row_count) {
    if (1 == row_count)
      return s;

    const char first_char{s[0]};

    if (all_of(begin(s), end(s),
               [&first_char](const char ch) { return ch == first_char; }))
      return s;

    vector<vector<char>> zigzag(row_count, vector<char>{});
    const size_t s_len{s.length()};

    string result{};
    result.reserve(s_len);
    int increment{1};

    for (size_t i{}, row_index{}; i < s_len; i++, row_index += increment) {
      zigzag[row_index].emplace_back(s[i]);
      if (i && !row_index)
        increment = -increment;
      else if (row_count - 1 == row_index)
        increment = -increment;
    }

    for (size_t i{}; i < zigzag.size(); i++) {
      for (size_t j{}; j < zigzag[i].size(); j++) {
        if (!zigzag[i][j])
          break;
        result.push_back(zigzag[i][j]);
      }
    }

    return result;
  }
};

int main() {
  Solution s{};

  cout << "s.convert(\"PAYPALISHIRING\", 3) -> "
       << s.convert(string{"PAYPALISHIRING"}, 3)
       << '\n';  // expected output: "PAHNAPLSIIGYIR"
  cout << "s.convert(\"PAYPALISHIRING\", 4) -> "
       << s.convert(string{"PAYPALISHIRING"}, 4)
       << '\n';  // expected output: "PINALSIGYAHRPI"

  return 0;
}