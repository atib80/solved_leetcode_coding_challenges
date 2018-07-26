/*
9. Leetcode coding challenge: Palindrome number

Determine whether an integer is a palindrome. An integer is a palindrome when it
reads the same backward as forward.

Example 1:

Input: 121
Output: true

Example 2:

Input: -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes
121-. Therefore it is not a palindrome.

Example 3:

Input: 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.

Follow up:

Coud you solve it without converting the integer to a string?
*/

#include <iomanip>
#include <iostream>

using namespace std;

class Solution {
 public:
  bool isPalindrome(const int x) {
    if (x < 0)
      return false;

    int source_x{x}, reversed_x{};

    while (source_x > 0) {
      reversed_x = 10 * reversed_x + source_x % 10;
      source_x /= 10;
    }

    return x == reversed_x;
  }
};

int main() {
  Solution s{};

  cout << boolalpha << "s.isPalindrome(121) -> " << s.isPalindrome(121)
       << '\n'  // expected output: true
       << "s.isPalindrome(-121) -> " << s.isPalindrome(-121)
       << '\n'  // expected output: false
       << "s.isPalindrome(10) -> " << s.isPalindrome(10)
       << '\n';  // expected output: false

  return 0;
}
