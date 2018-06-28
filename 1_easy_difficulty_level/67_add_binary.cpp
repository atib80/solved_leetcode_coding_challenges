/*
Given two binary strings, return their sum (also a binary string).

The input strings are both non-empty and contains only characters 1 or 0.

Example 1:

Input: a = "11", b = "1"
Output: "100"

Example 2:

Input: a = "1010", b = "1011"
Output: "10101"
*/

#include <deque>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

static int sres = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

class Solution {
 public:
  string addBinary(string a, string b) {
    const size_t a_len{a.length()};
    const size_t b_len{b.length()};
    string& shorter_op{a_len < b_len ? a : b};
    string& longer_op{!(a_len < b_len) ? a : b};
    const size_t shorter_op_len{shorter_op.length()};
    const size_t longer_op_len{longer_op.length()};
    if (!shorter_op_len)
      return longer_op;
    if (!longer_op_len)
      return shorter_op;
    if (shorter_op_len != longer_op_len)
      shorter_op.insert(begin(shorter_op), longer_op_len - shorter_op_len, '0');
    deque<char> buffer(longer_op_len + 1, '1');
    int carry{};
    for (int i = longer_op_len - 1; i >= 0; i--) {
      int sum{static_cast<int>(shorter_op[i] - '0') +
              static_cast<int>(longer_op[i] - '0') + carry};
      if (sum > 1) {
        sum %= 2;
        carry = 1;
      } else
        carry = 0;
      buffer[i + 1] = static_cast<char>(sum + '0');
    }

    if (!carry)
      buffer.pop_front();

    return string(begin(buffer), end(buffer));
  }
};

int main() {
  Solution s{};

  cout << "s.addBinary(\"11\", \"1\") -> "
       << s.addBinary(string{"11"}, string{"1"})
       << '\n';  // expected output: "100"
  cout << "s.addBinary(\"1010\", \"1011\") -> "
       << s.addBinary(string{"1010"}, string{"1011"})
       << '\n';  // expected output: "10101"
  cout << "s.addBinary(\"111\", \"1010\") -> "
       << s.addBinary(string{"111"}, string{"1010"})
       << '\n';  // expected output: "10001"
}