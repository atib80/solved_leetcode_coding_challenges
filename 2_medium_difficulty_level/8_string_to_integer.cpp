/*
8. Leetcode coding challenge: String to integer (atoi)

Implement atoi which converts a string to an integer.

The function first discards as many whitespace characters as necessary until the
first non-whitespace character is found. Then, starting from this character,
takes an optional initial plus or minus sign followed by as many numerical
digits as possible, and interprets them as a numerical value.

The string can contain additional characters after those that form the integral
number, which are ignored and have no effect on the behavior of this function.

If the first sequence of non-whitespace characters in str is not a valid
integral number, or if no such sequence exists because either str is empty or it
contains only whitespace characters, no conversion is performed.

If no valid conversion could be performed, a zero value is returned.

Note:

    Only the space character ' ' is considered as whitespace character.
    Assume we are dealing with an environment which could only store integers
within the 32-bit signed integer range: [−231,  231 − 1]. If the numerical value
is out of the range of representable values, INT_MAX (231 − 1) or INT_MIN (−231)
is returned.

Example 1:

Input: "42"
Output: 42

Example 2:

Input: "   -42"
Output: -42
Explanation: The first non-whitespace character is '-', which is the minus sign.
             Then take as many numerical digits as possible, which gets 42.

Example 3:

Input: "4193 with words"
Output: 4193
Explanation: Conversion stops at digit '3' as the next character is not a
numerical digit.

Example 4:

Input: "words and 987"
Output: 0
Explanation: The first non-whitespace character is 'w', which is not a numerical
             digit or a +/- sign. Therefore no valid conversion could be
performed.

Example 5:

Input: "-91283472332"
Output: -2147483648
Explanation: The number "-91283472332" is out of the range of a 32-bit signed
integer. Thefore INT_MIN (−2^31) is returned.
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

using namespace std;

string trim(const string& input) {
  string output{input};
  output.erase(begin(output),
               find_if(begin(output), end(output),
                       [](const char ch) { return !isspace(ch); }));

  output.erase(find_if(output.rbegin(), output.rend(),
                       [](const char ch) { return !isspace(ch); })
                   .base(),
               end(output));

  return output;
}

class Solution {
 public:
  int myAtoi(string str) {
    static const string upper_bound{"2147483647"};
    static const string lower_bound{"-2147483648"};
    const size_t ub_len{upper_bound.length()};
    const size_t lb_len{lower_bound.length()};

    str = trim(str);

    if (!isdigit(str[0]) && '-' != str[0] && '+' != str[0])
      return 0;

    const size_t num_start_pos{str.find_first_of("0123456789")};

    if (num_start_pos > 1)
      return 0;

    const size_t sign_pos{str.find_first_of("+-")};

    if (string::npos != sign_pos) {
      if (sign_pos > num_start_pos)
        str = str.substr(num_start_pos, sign_pos - num_start_pos);

      else if (count_if(begin(str) + sign_pos, begin(str) + num_start_pos,
                        [](const char ch) { return '-' == ch || '+' == ch; }) >
               1)
        return 0;
    }

    const bool is_number_negative{'-' == str[0]};

    size_t num_end_pos{str.find_first_not_of("0123456789", num_start_pos + 1)};

    if (string::npos != num_end_pos)
      str = str.substr(0, num_end_pos);

    if (is_number_negative) {
      while ('0' == str[1] && str.length() > 2)
        str.erase(1, 1);

      const size_t s_len{str.length()};

      if ((s_len > lb_len) || (s_len == lb_len && str >= lower_bound))
        return INT_MIN;

      str.erase(0, 1);

    } else if ('+' == str[0]) {
      str.erase(0, 1);
      while ('0' == str[0] && str.length() > 1)
        str.erase(0, 1);
    } else {
      while ('0' == str[0] && str.length() > 1)
        str.erase(0, 1);
    }

    if (!is_number_negative) {
      const size_t s_len{str.length()};
      if ((s_len > ub_len) || (s_len == ub_len && str >= upper_bound))
        return INT_MAX;
    }

    int result{};

    for (size_t i{}; i < str.length(); i++) {
      result *= 10;
      result += str[i] - '0';
    }

    if (is_number_negative)
      return -result;

    return result;
  }
};

int main() {
  Solution s{};

  cout << "s.myAtoi(\"42\") -> " << s.myAtoi("42")
       << '\n';  // expected output: 42
  cout << "s.myAtoi(\"   -42\") -> " << s.myAtoi("   -42")
       << '\n';  // expected output: -42
  cout << "s.myAtoi(\"4193 with words\") -> " << s.myAtoi("4193 with words")
       << '\n';  // expected output: 4193
  cout << "s.myAtoi(\"words and 987\") -> " << s.myAtoi("words and 987")
       << '\n';  // expected output: 0
  cout << "s.myAtoi(\"-91283472332\") -> " << s.myAtoi("-91283472332")
       << '\n';  // expected output: -2147483648 (INT_MIN: -2^31)

  return 0;
}