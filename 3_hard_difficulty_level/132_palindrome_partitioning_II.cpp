/*
132. Palindrome partitioning II (difficulty level: hard)

Given a string s, partition s such that every substring of the partition is a
palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

Example:

Input:  "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1
cut.
*/

#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
  unordered_map<char, vector<size_t>> char_positions_;
  string s_;
  size_t s_len_{};

  void find_minimum_number_of_cuts(
      const size_t start,     
      const size_t index,
      size_t& minimum_cuts,
      const size_t current_number_of_cuts = 0) const {
    if (current_number_of_cuts >= minimum_cuts)
      return;


  size_t last_index{index}, last_pos{char_positions_[s_[start]][index] + 1};

  while (last_pos > start) {

      if (is_palindromic_substr(start, last_pos)) {
        if (last_pos == s_len_) {
          if (current_number_of_cuts < minimum_cuts)
            minimum_cuts = current_number_of_cuts;
          return;
        }

        find_minimum_number_of_cuts(last_pos, char_positions_[s_[last_pos]].size() - 1, minimum_cuts, current_number_of_cuts + 1);
      } else {
      	if (!last_index) break;
      	--last_index;
      	last_pos = char_positions_[s_[start]][last_index] + 1;
      }
    }
  }

  inline bool is_palindromic_substr(const size_t start, const size_t last) const {
    if (start == last)
      return true;
    for (size_t i{start}, j{last - 1}; i < j; i++, j--) {
      if (s_[i] != s_[j])
        return false;
    }

    return true;
  }

 public:
  size_t minCut(string s) {
    s_len_ = s.length();

    if (s_len_ < 2)
      return 0;

    s_ = move(s);

    char_positions_.clear();

    for (size_t i{}; i < s_len_; ++i) char_positions_[s_[i]].emplace_back(i);

    size_t minimum_cuts{string::npos};
    find_minimum_number_of_cuts(0, char_positions_[s_[0]].size() - 1, minimum_cuts, 0);
    return minimum_cuts;
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

  cout << "s.minCut(\"aab\") -> " << s.minCut(string{"aab"})
       << '\n';  // expected output: 1

  cout << "s.minCut(\"fff\") -> " << s.minCut(string{"fff"})
       << '\n';  // expected output: 0
  cout << "s.minCut(\"abacabacrotor\") -> " << s.minCut(string{"abacabacrotor"})
       << '\n';  // expected output: 2

  // cout << "s.minCut("
  //         "\"apjesgpsxoeiokmqmfgvjslcjukbqxpsobyhjpbgdfruqdkeiszrlmtwgfxyfostpq"
  //         "czidfljwfbbrflkgdvtytbgqalguewnhvvmcgxboycffopmtmhtfizxkmeftcucxpobx"
  //         "melmjtuzigsxnncxpaibgpuijwhankxbplpyejxmrrjgeoevqozwdtgospohznkoyzoc"
  //         "jlracchjqnggbfeebmuvbicbvmpuleywrpzwsihivnrwtxcukwplgtobhgxukwrdlszf"
  //         "aiqxwjvrgxnsveedxseeyeykarqnjrtlaliyudpacctzizcftjlunlgnfwcqqxcqikoc"
  //         "qffsjyurzwysfjmswvhbrmshjuzsgpwyubtfbnwajuvrfhlccvfwhxfqthkcwhatktym"
  //         "gxostjlztwdxritygbrbibdgkezvzajizxasjnrcjwzdfvdnwwqeyumkamhzoqhnqjfz"
  //         "wzbixclcxqrtniznemxeahfozp\") -> "
  //      << s.minCut(string{
  //             "apjesgpsxoeiokmqmfgvjslcjukbqxpsobyhjpbgdfruqdkeiszrlmtwgfxyfost"
  //             "pqczidfljwfbbrflkgdvtytbgqalguewnhvvmcgxboycffopmtmhtfizxkmeftcu"
  //             "cxpobxmelmjtuzigsxnncxpaibgpuijwhankxbplpyejxmrrjgeoevqozwdtgosp"
  //             "ohznkoyzocjlracchjqnggbfeebmuvbicbvmpuleywrpzwsihivnrwtxcukwplgt"
  //             "obhgxukwrdlszfaiqxwjvrgxnsveedxseeyeykarqnjrtlaliyudpacctzizcftj"
  //             "lunlgnfwcqqxcqikocqffsjyurzwysfjmswvhbrmshjuzsgpwyubtfbnwajuvrfh"
  //             "lccvfwhxfqthkcwhatktymgxostjlztwdxritygbrbibdgkezvzajizxasjnrcjw"
  //             "zdfvdnwwqeyumkamhzoqhnqjfzwzbixclcxqrtniznemxeahfozp"})
  //      << '\n';

  cout << "Elapsed time: " << Solution::start_stop_timer() << " seconds\n";

  return 0;
}
