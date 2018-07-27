/*
125. Leetcode coding challenge: Valid palindrome

Given a string, determine if it is a palindrome, considering only alphanumeric
characters and ignoring cases.

Note: For the purpose of this problem, we define empty string as valid
palindrome.

Example 1:

Input: "A man, a plan, a canal: Panama"
Output: true

Example 2:

Input: "race a car"
Output: false
*/

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

class Solution {
 public:
  bool isPalindrome(const string& s) {
    const size_t str_len{s.length()};

    if (!str_len || 1 == str_len)
      return true;

    size_t i{}, j{str_len - 1};

    while (i < j) {
      if (!isalnum(s[i])) {
        i++;
      }

      else if (!isalnum(s[j])) {
        j--;
      }

      else if (tolower(s[i]) != tolower(s[j]))
        return false;

      else {
        i++;
        j--;
      }
    }

    return true;
  }
};

int main() {
  Solution s{};

  cout << boolalpha
       << "s.isPalindrome(\"Anne, I vote more cars race Rome-to-Vienna\") -> "
       << s.isPalindrome("Anne, I vote more cars race Rome-to-Vienna")
       << '\n'  // expected: true
       << "s.isPalindrome(\"Noel - sees Leon\") -> "
       << s.isPalindrome("Noel - sees Leon") << '\n'  // expected: true
       << "s.isPalindrome(\"A man, a plan, a canal: Panama\") -> "
       << s.isPalindrome("A man, a plan, a canal: Panama")
       << '\n'  // expected: true
       << "s.isPalindrome(\"race a car\") -> " << s.isPalindrome("race a car")
       << '\n'  // expected: false
       << "s.isPalindrome(\"aA\") -> " << s.isPalindrome("aA")
       << '\n'  // expected: true
       << "s.isPalindrome(\"a A a\") -> " << s.isPalindrome("a A a")
       << '\n'  // expected: true
       << "s.isPalindrome(\"A war at Tarawa!\") -> "
       << s.isPalindrome("A war at Tarawa!") << noboolalpha
       << '\n';  // expected: true

  return 0;
}