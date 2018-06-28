/*
65. Leetcode coding challenge: Valid number

Validate if a given string is numeric.

Some examples:
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true

Note: It is intended for the problem statement to be ambiguous. You should
gather all requirements up front before implementing one.
*/

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  static string trim(string str) {
    const size_t str_len{str.length()};

    if (!str_len)
      return string{};

    size_t begin_str{};
    size_t end_str{str_len - 1};

    for (; begin_str <= end_str; ++begin_str) {
      if (!isspace(str[begin_str]))
        break;
    }

    if (begin_str > end_str)
      return string{};

    for (; end_str > begin_str; --end_str) {
      if (!isspace(str[end_str]))
        break;
    }

    if (0 == begin_str && str_len - 1 == end_str)
      return str;

    return str.substr(begin_str, end_str - begin_str + 1);
  }

  bool isNumber(string s) {
    s = trim(move(s));
    const size_t s_len{s.length()};

    if (string::npos == s.find_first_of("0123456789"))
      return false;

    if (0 != s.find_first_of("+-.0123456789"))
      return false;

    if (string::npos != s.find_first_not_of("1234567890.+-eE"))
      return false;

    if (s_len - 1 == s.find_first_of("+-eE", s_len - 1))
      return false;

    if (0 == s.find(".e") || 0 == s.find(".E"))
      return false;

    if (string::npos != s.find("+E") || string::npos != s.find("-E") ||
        string::npos != s.find("+e") || string::npos != s.find("-e"))
      return false;

    const auto number_of_dots = count(begin(s), end(s), '.');

    if (1 == number_of_dots && 1 == s_len)
      return false;

    if (number_of_dots > 1)
      return false;

    const auto number_of_scientific_signs = count_if(
        begin(s), end(s), [](const char ch) { return 'e' == ch || 'E' == ch; });

    if (number_of_scientific_signs > 1)
      return false;

    const size_t scientific_sign_pos{s.find_first_of("eE")};

    if (1 == number_of_dots) {
      const size_t dot_pos{s.find('.')};

      if ((string::npos != dot_pos) &&
          (dot_pos < s.length() - 1 &&
           s.find_first_of("eE0123456789", dot_pos + 1) != dot_pos + 1))
        return false;

      if (string::npos != scientific_sign_pos && string::npos != dot_pos &&
          scientific_sign_pos < dot_pos)
        return false;
    }

    const auto number_of_number_signs = count_if(
        begin(s), end(s), [](const char ch) { return '-' == ch || '+' == ch; });

    if (number_of_number_signs > 2 || string::npos != s.find("++") ||
        string::npos != s.find("--") || string::npos != s.find("-+") ||
        string::npos != s.find("+-"))
      return false;

    const size_t sign_pos{s.find_first_of("+-")};

    if (string::npos == scientific_sign_pos && string::npos != sign_pos &&
        0 != sign_pos)
      return false;

    if (string::npos != scientific_sign_pos) {
      if ((scientific_sign_pos == s.length() - 1) ||
          (scientific_sign_pos + 1 < s.length() &&
           s.find_first_of("+-0123456789", scientific_sign_pos + 1) !=
               scientific_sign_pos + 1) ||
          (scientific_sign_pos + 2 < s.length() &&
           s.find_first_of("+-", scientific_sign_pos + 1) ==
               scientific_sign_pos + 1 &&
           s.find_first_of("0123456789", scientific_sign_pos + 2) !=
               scientific_sign_pos + 2))
        return false;

      if (scientific_sign_pos + 2 < s.length() &&
          s.find_first_of("+-", scientific_sign_pos + 1) ==
              scientific_sign_pos + 1 &&
          (s[scientific_sign_pos + 2] < '0' ||
           s[scientific_sign_pos + 2] > '9'))
        return false;
    }

    return true;
  }
};

int main() {
  Solution s{};
  cout << boolalpha << "s.isNumber(string{\"0\"}) -> "
       << s.isNumber(string{"0"}) << '\n';  // expected output: true
  cout << "s.isNumber(string{\" 0.1 \"}) -> " << s.isNumber(string{" 0.1 "})
       << '\n';  // expected output: true
  cout << "s.isNumber(string{\"abc\"}) -> " << s.isNumber(string{"abc"})
       << '\n';  // expected output: false
  cout << "s.isNumber(string{\"1 a\"}) -> " << s.isNumber(string{"1 a"})
       << '\n';  // expected output: false
  cout << "s.isNumber(string{\"2e10\"}) -> " << s.isNumber(string{"2e10"})
       << '\n';  // expected output: true
  cout << "s.isNumber(string{\".1\"}) -> " << s.isNumber(string{".1"})
       << '\n';  // expected output: true
  cout << "s.isNumber(string{\"3.\"}) -> " << s.isNumber(string{"3."})
       << '\n';  // expected output: true
  cout << "s.isNumber(string{\"4e+\"}) -> " << s.isNumber(string{"4e+"})
       << '\n';  // expected output: false
  cout << "s.isNumber(string{\"46.e3\"}) -> " << s.isNumber(string{"46.e3"})
       << '\n';  // expected output: true
  cout << "s.isNumber(string{\"6e6.5\"}) -> " << s.isNumber(string{"6e6.5"})
       << '\n';  // expected output: false
  cout << "s.isNumber(string{\"92e1740e91\"}) -> "
       << s.isNumber(string{"92e1740e91"}) << '\n';  // expected output: false
  cout << "s.isNumber(string{\"2e+60++604\"}) -> "
       << s.isNumber(string{"2e+60++604"}) << '\n';  // expected output: false
  cout << "s.isNumber(string{\"e8\"}) -> " << s.isNumber(string{"e8"})
       << noboolalpha << '\n';  // expected output: false

  return 0;
}
