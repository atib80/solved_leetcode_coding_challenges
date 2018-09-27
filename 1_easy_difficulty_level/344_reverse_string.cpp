/*
344. Reverse string (difficulty level: easy)

Write a function that takes a string as input and returns the string reversed.

Example 1:

Input: "hello"
Output: "olleh"

Example 2:

Input: "A man, a plan, a canal: Panama"
Output: "amanaP :lanac a ,nalp a ,nam A"
*/

#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>

using namespace std;

class Solution {
 public:
  string reverseString(string s) const {
    const size_t s_len{s.length()};
    if (s_len < 2)
      return move(s);

    for (size_t i{}, j{s.length() - 1}; i < j; i++, j--)
      swap(s[i], s[j]);

    return move(s);
  }

  static double start_stop_timer(const bool is_start_timer = false) {
    static chrono::high_resolution_clock::time_point start_time;
    if (is_start_timer)
      start_time = chrono::high_resolution_clock::now();

    return chrono::duration_cast<chrono::duration<double>>(
               chrono::high_resolution_clock::now() - start_time)
        .count();
  }
};

int main() {
  Solution s{};

  Solution::start_stop_timer(true);
  cout << "s.reverseString(\"A man, a plan, a canal: Panama\") -> "
       << s.reverseString(string{"A man, a plan, a canal: Panama"}) << '\n';

  cout << "Elapsed time: " << Solution::start_stop_timer() << " seconds\n";

  return 0;
}
