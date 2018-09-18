/*
13. Roman to integer (difficulty level: easy)

Roman numerals are represented by seven different symbols: I, V, X, L, C, D and
M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000

For example, two is written as II in Roman numeral, just two one's added
together. Twelve is written as, XII, which is simply X + II. The number twenty
seven is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right.
However, the numeral for four is not IIII. Instead, the number four is written
as IV. Because the one is before the five we subtract it making four. The same
principle applies to the number nine, which is written as IX. There are six
instances where subtraction is used:

    I can be placed before V (5) and X (10) to make 4 and 9.
    X can be placed before L (50) and C (100) to make 40 and 90.
    C can be placed before D (500) and M (1000) to make 400 and 900.

Given a roman numeral, convert it to an integer. Input is guaranteed to be
within the range from 1 to 3999.

Example 1:

Input: "III"
Output: 3

Example 2:

Input: "IV"
Output: 4

Example 3:

Input: "IX"
Output: 9

Example 4:

Input: "LVIII"
Output: 58
Explanation: C = 100, L = 50, XXX = 30 and III = 3.

Example 5:

Input: "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
 public:
  int romanToInt(const string& s) {
    static unordered_map<string, int> roman_arabic_dict{
        {"I", 1},      {"II", 2},    {"III", 3},  {"IV", 4},    {"V", 5},
        {"VI", 6},     {"VII", 7},   {"VIII", 8}, {"IX", 9},    {"X", 10},
        {"XX", 20},    {"XXX", 30},  {"XL", 40},  {"L", 50},    {"LX", 60},
        {"LXX", 70},   {"LXXX", 80}, {"XC", 90},  {"C", 100},   {"CC", 200},
        {"CCC", 300},  {"CD", 400},  {"D", 500},  {"DC", 600},  {"DCC", 700},
        {"DCCC", 800}, {"CM", 900},  {"M", 1000}, {"MM", 2000}, {"MMM", 3000}};

    int result{};
    size_t current_pos{s.length()};
    string index{};
    index.reserve(8);
    while (true) {
      size_t len{4};
      if (current_pos < 4)
        len = current_pos;
      for (; len > 0; --len) {
        index.clear();
        copy(cbegin(s) + current_pos - len, cbegin(s) + current_pos,
             back_inserter(index));
        if (roman_arabic_dict.find(index) != end(roman_arabic_dict)) {
          result += roman_arabic_dict.at(index);
          current_pos -= len;
          if (!current_pos)
            return result;
          break;
        }
      }
    }
  }
};

int main() {
  Solution s{};

  cout << "s.romanToInt(\"III\") -> " << s.romanToInt("III")
       << '\n';  // expected output: 3
  cout << "s.romanToInt(\"IV\") -> " << s.romanToInt("IV")
       << '\n';  // expected output: 4
  cout << "s.romanToInt(\"IX\") -> " << s.romanToInt("IX")
       << '\n';  // expected output: 9
  cout << "s.romanToInt(\"LVIII\") -> " << s.romanToInt("LVIII")
       << '\n';  // expected output: 58
  cout << "s.romanToInt(\"MCMXCIV\") -> " << s.romanToInt("MCMXCIV")
       << '\n';  // expected output: 1994

  return 0;
}
