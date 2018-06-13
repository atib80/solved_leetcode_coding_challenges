/*
Given two non-negative integers num1 and num2 represented as strings, return the
product of num1 and num2, also represented as a string.

Example 1:

Input:  num1 = "2", num2 = "3"
Output: "6"

Example 2:

Input:  num1 = "123", num2 = "456"
Output: "56088"

Note:

    The length of both num1 and num2 is < 110.
    Both num1 and num2 contain only digits 0-9.
    Both num1 and num2 do not contain any leading zero, except the number 0
itself. You must not use any built-in BigInteger library or convert the inputs
to integer directly.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::max;
using std::min;
using std::string;
using std::vector;

class Solution {
 public:
  string multiply(string num1, string num2) {
    if (num1 == "0" || num2 == "0")
      return "0";
    if (num1 == "1")
      return num2;
    if (num2 == "1")
      return num1;

    const size_t num1_len{num1.length()};
    const size_t num2_len{num2.length()};

    size_t start{};

    if ('1' == num1[start]) {
      ++start;
      size_t number_of_zeroes{};
      while ('0' == num1[start]) {
        ++number_of_zeroes;
        ++start;
      }

      if (num1_len == start) {
        num2 += string(number_of_zeroes, '0');
        return num2;
      }
    }

    start = 0;

    if ('1' == num2[start]) {
      ++start;
      size_t number_of_zeroes{};
      while ('0' == num2[start]) {
        ++number_of_zeroes;
        ++start;
      }

      if (num2_len == start) {
        num1 += string(number_of_zeroes, '0');
        return num1;
      }
    }

    for (char& d : num1)
      d -= '0';
    for (char& d : num2)
      d -= '0';

    const string& max_num{num1_len >= num2_len ? num1 : num2};
    const string& min_num{num1_len < num2_len ? num1 : num2};
    const size_t max_num_len{max_num.length()};
    const size_t min_num_len{min_num.length()};

    vector<vector<int>> products(min_num_len + 1,
                                 vector<int>(min_num_len + max_num_len + 2, 0));

    int carry{};
    for (int i = min_num_len - 1, k{}; i >= 0; i--, k++) {
      int l{};
      for (int j = max_num_len - 1; j >= 0; j--, l++) {
        int product{max_num[j] * min_num[i] + carry};
        carry = product / 10;
        products[k][min_num_len + max_num_len + 1 - k - l] = product % 10;
      }

      while (carry) {
        products[k][min_num_len + max_num_len + 1 - k - l] = carry % 10;
        carry /= 10;
        l++;
      }
    }

    carry = 0;

    for (size_t j{min_num_len + max_num_len + 1}; j >= 1; j--) {
      int sum{carry};

      for (size_t i{}; i < min_num_len; i++)
        sum += products[i][j];

      products[min_num_len][j] = sum % 10;
      carry = sum / 10;
    }

    products[min_num_len][0] = carry;

    string result{};

    bool skip_zero{true};

    for (const int d : products[min_num_len]) {
      if (!d && skip_zero)
        continue;
      skip_zero = false;
      result.push_back(static_cast<char>(d + '0'));
    }

    return result;
  }
};

int main() {
  Solution s{};
  cout << "s.multiply(\"2\", \"3\") -> " << s.multiply("2", "3")
       << '\n';  // expected output: "6"
  cout << "s.multiply(\"123\", \"456\") -> " << s.multiply("123", "456")
       << '\n';  // expected output: "56088"
  cout << "s.multiply(\"9\", \"9\") -> " << s.multiply("9", "9")
       << '\n';  // expected output: "81"
  cout << "s.multiply(\"999\", \"999\") -> " << s.multiply("999", "999")
       << '\n';  // expected output: "998001"

  return 0;
}