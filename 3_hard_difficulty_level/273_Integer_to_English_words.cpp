/*
273. Integer to English words (difficulty level: hard)

Convert a non-negative integer to its english words representation. Given input
is guaranteed to be less than 231 - 1.

Example 1:

Input: 123
Output: "One Hundred Twenty Three"

Example 2:

Input: 12345
Output: "Twelve Thousand Three Hundred Forty Five"

Example 3:

Input: 1234567
Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"

Example 4:

Input: 1234567891
Output: "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven
Thousand Eight Hundred Ninety One"
*/

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
  static const unordered_map<int, string> arabic_numerals;

  static int get_number_of_billions(int num, string& output) {
    const int factor{num / 1000000000};

    if (factor) {
      output += arabic_numerals.at(factor);
      output += " Billion";
      num -= factor * 1000000000;
    }

    return num;
  }

  static int get_number_of_millions(int num, string& output) {
    if (num < 1000000)
      return num;
    const int ret_num{num % 1000000};
    num %= 1000000000;
    num /= 1000000;
    int factor{num / 100};
    if (factor) {
      if (!output.empty())
        output.push_back(' ');
      output += arabic_numerals.at(factor);
      output += " Hundred";
      num -= factor * 100;
    }

    factor = (num / 10) * 10;
    if (factor) {
      if (!output.empty())
        output.push_back(' ');
      output += arabic_numerals.at(factor);
      num -= factor;
    }

    if (num) {
      if (!output.empty())
        output.push_back(' ');
      output += arabic_numerals.at(num);
    }

    if (!output.empty())
      output += " Million";

    return ret_num;
  }

  static int get_number_of_thousands(int num, string& output) {
    if (num < 1000)
      return num;
    const int ret_num{num % 1000};
    num %= 1000000;
    num /= 1000;
    int factor{num / 100};
    if (factor) {
      if (!output.empty())
        output.push_back(' ');
      output += arabic_numerals.at(factor);
      output += " Hundred";
      num -= factor * 100;
    }

    factor = (num / 10) * 10;
    if (factor) {
      if (!output.empty())
        output.push_back(' ');
      output += arabic_numerals.at(factor);
      num -= factor;
    }

    if (num) {
      if (!output.empty())
        output.push_back(' ');
      output += arabic_numerals.at(num);
    }

    if (!output.empty())
      output += " Thousand";

    return ret_num;
  }

  static void get_number_less_than_thousand(int num, string& output) {
    if (!num)
      return;

    int factor{num / 100};
    if (factor) {
      if (!output.empty())
        output.push_back(' ');
      output += arabic_numerals.at(factor);
      output += " Hundred";
      num -= factor * 100;
    }

    factor = (num / 10) * 10;
    if (factor) {
      if (!output.empty())
        output.push_back(' ');
      output += arabic_numerals.at(factor);
      num -= factor;
    }

    if (num) {
      if (!output.empty())
        output.push_back(' ');
      output += arabic_numerals.at(num);
    }
  }

 public:
  string numberToWords(int num) const {
    string output{};
    if (!num)
      return output;
    output.reserve(256);
    num = get_number_of_billions(num, output);
    num = get_number_of_millions(num, output);
    num = get_number_of_thousands(num, output);
    get_number_less_than_thousand(num, output);

    return output;
  }
};

const unordered_map<int, string> Solution::arabic_numerals{
    {1, "One"},
    {2, "Two"},
    {3, "Three"},
    {4, "Four"},
    {5, "Five"},
    {6, "Six"},
    {7, "Seven"},
    {8, "Eight"},
    {9, "Nine"},
    {10, "Ten"},
    {11, "Eleven"},
    {12, "Twelve"},
    {13, "Thirteen"},
    {14, "Fourteen"},
    {15, "Fifteen"},
    {16, "Sixteen"},
    {17, "Seventeen"},
    {18, "Eighteen"},
    {19, "Nineteen"},
    {20, "Twenty"},
    {30, "Thirty"},
    {40, "Fourty"},
    {50, "Fifty"},
    {60, "Sixty"},
    {70, "Seventy"},
    {80, "Eighty"},
    {90, "Ninety"},
    {100, "Hundred"},
    {1000, "Thousand"},
    {1000000, "Million"},
    {1000000000, "Billion"}};

int main() {
  Solution s{};

  cout << "s.numberToWords(123) -> " << s.numberToWords(123)
       << '\n';  // expected output: "One Hundred Twenty Three"
  cout << "s.numberToWords(12345) -> " << s.numberToWords(12345)
       << '\n';  // expected output: "Twelve Thousand Three Hundred Forty Five"
  cout << "s.numberToWords(1234567) -> " << s.numberToWords(1234567)
       << '\n';  // expected output: "One Million Two Hundred Thirty Four
                 // Thousand Five Hundred Sixty Seven"
  cout << "s.numberToWords(1234567891) -> " << s.numberToWords(1234567891)
       << '\n';  // expected output: "One Billion Two Hundred Thirty Four
                 // Million Five Hundred Sixty Seven Thousand Eight Hundred
                 // Ninety One"

  return 0;
}
