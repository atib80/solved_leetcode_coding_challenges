/*
171. Leetcode coding challenge: Excel sheet column number

Given a column title as appear in an Excel sheet, return its corresponding
column number.

For example:

    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28
    ...

Example 1:

Input: "A"
Output: 1

Example 2:

Input: "AB"
Output: 28

Example 3:

Input: "ZY"
Output: 701
*/

#include <cmath>
#include <iostream>
#include <string>

using namespace std;

class Solution {
 public:
  int titleToNumber(const string& s) {
    const size_t s_len{s.length()};
    int column_index{};

    for (size_t i{}; i < s_len; i++) {
      const int factor{static_cast<int>(s[i] - 'A' + 1)};
      column_index += factor * static_cast<int>(pow(26u, s_len - i - 1));
    }

    return column_index;
  }
};

int main() {
  Solution s{};

  cout << "s.titleToNumber(\"A\") -> " << s.titleToNumber("A")
       << '\n';  // expected output: 1
  cout << "s.titleToNumber(\"AB\") -> " << s.titleToNumber("AB")
       << '\n';  // expected output: 28
  cout << "s.titleToNumber(\"ZY\") -> " << s.titleToNumber("ZY")
       << '\n';  // expected output: "701"
  cout << "s.titleToNumber(\"AA\") -> " << s.titleToNumber("AA")
       << '\n';  // expected output: 27
  cout << "s.titleToNumber(\"AZ\") -> " << s.titleToNumber("AZ")
       << '\n';  // expected output: "52"

  return 0;
}
