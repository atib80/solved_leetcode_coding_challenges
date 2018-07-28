/*
168. Leetcode coding challenge: Excel sheet column title

Given a positive integer, return its corresponding column title as appear in an
Excel sheet.

For example:

    1 -> A
    2 -> B
    3 -> C
    ...
    26 -> Z
    27 -> AA
    28 -> AB
    ...

Example 1:

Input: 1
Output: "A"

Example 2:

Input: 28
Output: "AB"

Example 3:

Input: 701
Output: "ZY"
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
 public:
  string convertToTitle(int n) {
    static const string ABC_lookup{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    string column_title{};
    column_title.reserve(12);

    while (n > 0) {
      const int index{(25 + n % 26) % 26};
      column_title.insert(0, 1, ABC_lookup[index]);
      n /= 26;
      if (25 == index)
        n--;
    }

    return column_title;
  }
};

int main() {
  Solution s{};

  cout << "s.convertToTitle(1) -> " << s.convertToTitle(1)
       << '\n';  // expected output: "A"
  cout << "s.convertToTitle(28) -> " << s.convertToTitle(28)
       << '\n';  // expected output: "AB"
  cout << "s.convertToTitle(701) -> " << s.convertToTitle(701)
       << '\n';  // expected output: "ZY"
  cout << "s.convertToTitle(27) -> " << s.convertToTitle(27)
       << '\n';  // expected output: "AA"
  cout << "s.convertToTitle(52) -> " << s.convertToTitle(52)
       << '\n';  // expected output: "AZ"

  return 0;
}
