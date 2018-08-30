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

 public:
  string convert_number_to_english_words(int number) const {
    if (!number)
      return "Zero";
    string output{};
    output.reserve(256);

    int factor{number / 1000000000};

    if (factor) {
      output += arabic_numerals.at(factor);
      output += " Billion";
      number %= 1000000000;
    }

    if (number >= 1000000) {
      const int thousands{number % 1000000};
      number /= 1000000;
      factor = number / 100;
      if (factor) {
        if (!output.empty())
          output.push_back(' ');
        output += arabic_numerals.at(factor);
        output += " Hundred";
        number %= 100;
      }

      if (arabic_numerals.find(number) != end(arabic_numerals)) {
        if (!output.empty())
          output.push_back(' ');
        output += arabic_numerals.at(number);
        output += " Million";
      } else {
        factor = number - (number % 10);
        if (factor) {
          if (!output.empty())
            output.push_back(' ');
          output += arabic_numerals.at(factor);
        }

        number %= 10;

        if (number) {
          if (!output.empty())
            output.push_back(' ');
          output += arabic_numerals.at(number);
        }

        if (!output.empty())
          output += " Million";
      }

      number = thousands;
    }

    if (number >= 1000) {
      int remainder{number % 1000};
      number /= 1000;
      factor = number / 100;
      if (factor) {
        if (!output.empty())
          output.push_back(' ');
        output += arabic_numerals.at(factor);
        output += " Hundred";
        number %= 100;
      }

      if (arabic_numerals.find(number) != end(arabic_numerals)) {
        if (!output.empty())
          output.push_back(' ');
        output += arabic_numerals.at(number);
        output += " Thousand";
      } else {
        factor = number - (number % 10);
        if (factor) {
          if (!output.empty())
            output.push_back(' ');
          output += arabic_numerals.at(factor);
        }

        number %= 10;

        if (number) {
          if (!output.empty())
            output.push_back(' ');
          output += arabic_numerals.at(number);
        }

        if (!output.empty())
          output += " Thousand";
      }

      number = remainder;
    }

    if (!number)
      return output;
    factor = number / 100;
    if (factor) {
      if (!output.empty())
        output.push_back(' ');
      output += arabic_numerals.at(factor);
      output += " Hundred";
      number %= 100;
    }

    if (arabic_numerals.find(number) != end(arabic_numerals)) {
      if (!output.empty())
        output.push_back(' ');
      output += arabic_numerals.at(number);
      return output;
    }

    factor = number - (number % 10);
    if (factor) {
      if (!output.empty())
        output.push_back(' ');
      output += arabic_numerals.at(factor);
    }

    number %= 10;

    if (number) {
      if (!output.empty())
        output.push_back(' ');
      output += arabic_numerals.at(number);
    }

    return output;
  }

  string numberToWords(int number) const {
    return convert_number_to_english_words(number);
  }
};

const unordered_map<int, string> Solution::arabic_numerals{
    {1, "One"},        {2, "Two"},       {3, "Three"},     {4, "Four"},
    {5, "Five"},       {6, "Six"},       {7, "Seven"},     {8, "Eight"},
    {9, "Nine"},       {10, "Ten"},      {11, "Eleven"},   {12, "Twelve"},
    {13, "Thirteen"},  {14, "Fourteen"}, {15, "Fifteen"},  {16, "Sixteen"},
    {17, "Seventeen"}, {18, "Eighteen"}, {19, "Nineteen"}, {20, "Twenty"},
    {30, "Thirty"},    {40, "Forty"},    {50, "Fifty"},    {60, "Sixty"},
    {70, "Seventy"},   {80, "Eighty"},   {90, "Ninety"}};

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
  cout << "s.numberToWords(12345) -> " << s.numberToWords(12345)
       << '\n';  // expected output: "Twelve Thousand Three Hundred Forty Five"
  cout << "s.numberToWords(0) -> " << s.numberToWords(0)
       << '\n';  // expected output: "Zero"

  return 0;
}
