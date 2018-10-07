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
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  unordered_map<char, vector<size_t>> char_positions_;
  unordered_set<string_view> ignored_substrings_;
  string s_;
  size_t s_len_{};

  void find_minimum_number_of_cuts(const size_t start,
                                   const size_t index,
                                   size_t& minimum_cuts,
                                   const size_t current_number_of_cuts = 0) {
    if (current_number_of_cuts + s_len_ - start >= minimum_cuts)
      return;

    size_t last_index{index}, last_pos{char_positions_[s_[start]][index] + 1};
    size_t index_of_first_differing_chars{start + 1};

    while (true) {
      const string_view palindromic_substr{&s_[start], last_pos - start};
      if (ignored_substrings_.find(palindromic_substr) ==
          end(ignored_substrings_)) {
        if (last_pos - start < 2 ||
            is_palindromic_substr(start, last_pos,
                                  index_of_first_differing_chars)) {
          if (last_pos == s_len_) {
            if (current_number_of_cuts < minimum_cuts)
              minimum_cuts = current_number_of_cuts;
            return;
          }

          if (current_number_of_cuts + 1 < minimum_cuts)
            find_minimum_number_of_cuts(
                last_pos, char_positions_[s_[last_pos]].size() - 1,
                minimum_cuts, current_number_of_cuts + 1);
        } else
          ignored_substrings_.emplace(palindromic_substr);
      }

      if (!last_index) {
        ignored_substrings_.emplace(&s_[start],
                                    index_of_first_differing_chars - start + 1);
        return;
      }

      --last_index;
      last_pos = char_positions_[s_[start]][last_index] + 1;
      if (last_pos <= start)
        return;
      if (last_pos - start == 1)
        ignored_substrings_.emplace(&s_[start],
                                    index_of_first_differing_chars - start + 1);
    }
  }

  inline bool is_palindromic_substr(const size_t start,
                                    const size_t last,
                                    size_t& index_of_first_differing_chars) {
    for (size_t i{start + 1}, j{last - 2}; i < j; i++, j--) {
      if (s_[i] != s_[j]) {
        if (i > index_of_first_differing_chars)
          index_of_first_differing_chars = i;
        return false;
      }
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

    for (size_t i{}; i < s_len_; ++i)
      char_positions_[s_[i]].emplace_back(i);

    ignored_substrings_.clear();

    size_t minimum_cuts{string::npos};
    find_minimum_number_of_cuts(0, char_positions_[s_[0]].size() - 1,
                                minimum_cuts, 0);
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
  cout << "s.minCut(\"abxacabzacrotor\") -> "
       << s.minCut(string{"abxacabzacrotor"}) << '\n';  // expected output: 9

  cout << "s.minCut("
          "\"apjesgpsxoeiokmqmfgvjslcjukbqxpsobyhjpbgdfruqdkeiszrlmtwgfxyfost"
          "pq"
          "czidfljwfbbrflkgdvtytbgqalguewnhvvmcgxboycffopmtmhtfizxkmeftcucxpo"
          "bx"
          "melmjtuzigsxnncxpaibgpuijwhankxbplpyejxmrrjgeoevqozwdtgospohznkoyz"
          "oc"
          "jlracchjqnggbfeebmuvbicbvmpuleywrpzwsihivnrwtxcukwplgtobhgxukwrdls"
          "zf"
          "aiqxwjvrgxnsveedxseeyeykarqnjrtlaliyudpacctzizcftjlunlgnfwcqqxcqik"
          "oc"
          "qffsjyurzwysfjmswvhbrmshjuzsgpwyubtfbnwajuvrfhlccvfwhxfqthkcwhatkt"
          "ym"
          "gxostjlztwdxritygbrbibdgkezvzajizxasjnrcjwzdfvdnwwqeyumkamhzoqhnqj"
          "fz"
          "wzbixclcxqrtniznemxeahfozp\") -> "
       << s.minCut(
              string{"apjesgpsxoeiokmqmfgvjslcjukbqxpsobyhjpbgdfruqdkeiszrlmt"
                     "wgfxyfost"
                     "pqczidfljwfbbrflkgdvtytbgqalguewnhvvmcgxboycffopmtmhtfi"
                     "zxkmeftcu"
                     "cxpobxmelmjtuzigsxnncxpaibgpuijwhankxbplpyejxmrrjgeoevq"
                     "ozwdtgosp"
                     "ohznkoyzocjlracchjqnggbfeebmuvbicbvmpuleywrpzwsihivnrwt"
                     "xcukwplgt"
                     "obhgxukwrdlszfaiqxwjvrgxnsveedxseeyeykarqnjrtlaliyudpac"
                     "ctzizcftj"
                     "lunlgnfwcqqxcqikocqffsjyurzwysfjmswvhbrmshjuzsgpwyubtfb"
                     "nwajuvrfh"
                     "lccvfwhxfqthkcwhatktymgxostjlztwdxritygbrbibdgkezvzajiz"
                     "xasjnrcjw"
                     "zdfvdnwwqeyumkamhzoqhnqjfzwzbixclcxqrtniznemxeahfozp"})
       << '\n';

  cout << "Elapsed time: " << Solution::start_stop_timer() << " seconds\n";

  return 0;
}
