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
  static const unordered_map<int64_t, string> arabic_numerals;

 public:
  string convert_number_to_english_words(int64_t number) const {
    static const int64_t div_factors[]{1000000000000000000LL,
                                       1000000000000000LL,
                                       1000000000000LL,
                                       1000000000LL,
                                       1000000LL,
                                       1000LL,
                                       1LL,
                                       0LL};
    if (!number)
      return arabic_numerals.at(0);
    string output{};
    output.reserve(256);

    if (number < 0)
      output += arabic_numerals.at(-1);

    for (const int64_t div_factor : div_factors) {
      if (!div_factor || !number)
        break;

      int64_t factor{number / div_factor};

      if (number >= div_factor) {
        const int64_t remainder{number % div_factor};
        number /= div_factor;
        factor = number / 100;
        if (factor) {
          if (!output.empty())
            output.push_back(' ');
          output += arabic_numerals.at(factor);
          output.push_back(' ');
          output += arabic_numerals.at(100);
          number %= 100;
        }

        if (arabic_numerals.find(number) != end(arabic_numerals)) {
          if (!output.empty())
            output.push_back(' ');
          output += arabic_numerals.at(number);
          if (1 != div_factor) {
            output.push_back(' ');
            output += arabic_numerals.at(div_factor);
          }
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

          if (!output.empty() && 1 != div_factor) {
            output.push_back(' ');
            output += arabic_numerals.at(div_factor);
          }
        }

        number = remainder;
      }
    }

    return output;
  }

  string numberToWords(int64_t number) const {
    return convert_number_to_english_words(number);
  }
};

const unordered_map<int64_t, string> Solution::arabic_numerals{
    {-1LL, "Minus"},
    {0LL, "Zero"},
    {1LL, "One"},
    {2LL, "Two"},
    {3LL, "Three"},
    {4LL, "Four"},
    {5LL, "Five"},
    {6LL, "Six"},
    {7LL, "Seven"},
    {8LL, "Eight"},
    {9LL, "Nine"},
    {10LL, "Ten"},
    {11LL, "Eleven"},
    {12LL, "Twelve"},
    {13LL, "Thirteen"},
    {14LL, "Fourteen"},
    {15LL, "Fifteen"},
    {16LL, "Sixteen"},
    {17LL, "Seventeen"},
    {18LL, "Eighteen"},
    {19LL, "Nineteen"},
    {20LL, "Twenty"},
    {30LL, "Thirty"},
    {40LL, "Forty"},
    {50LL, "Fifty"},
    {60LL, "Sixty"},
    {70LL, "Seventy"},
    {80LL, "Eighty"},
    {90LL, "Ninety"},
    {100LL, "Hundred"},
    {1000LL, "Thousand"},
    {1000000LL, "Million"},
    {1000000000LL, "Billion"},
    {1000000000000LL, "Trillion"},
    {1000000000000000LL, "Quadrillion"},
    {1000000000000000000LL, "Quintillion"}};

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
  cout
      << "s.numberToWords(12345678912345678) -> "
      << s.numberToWords(12345678912345678LL)
      << '\n';  // expected output: "Twelve Quadrillion Three Hundred Forty Five
                // Trillion Six Hundred Seventy Eight Billion Nine Hundred
                // Twelve Million Three Hundred Forty Five Thousand Six Hundred
                // Seventy Eight"
  cout << "s.numberToWords(0) -> " << s.numberToWords(0)
       << '\n';  // expected output: "Zero"

  return 0;
}
