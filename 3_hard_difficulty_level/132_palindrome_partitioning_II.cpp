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

#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct palindromic_interval {
  size_t start;
  size_t last;
  size_t number_of_cuts;

  palindromic_interval(const size_t start,
                       const size_t last,
                       const size_t number_of_cuts)
      : start{start}, last{last}, number_of_cuts{number_of_cuts} {}
};

static size_t s_len;

// namespace std {
template <>
struct hash<pair<size_t, size_t>> {
  size_t operator()(const pair<size_t, size_t>& p) const noexcept {
    return p.first * s_len + p.second;
  }
};
// }  // namespace std

class Solution {
  unordered_map<char, vector<size_t>> char_positions_;
  multimap<size_t, size_t> palindromic_substring_intervals_;
  unordered_map<pair<size_t, size_t>, size_t>
      min_number_of_registered_cuts_at_nodes_;
  vector<palindromic_interval>
      currently_visited_palindromic_substring_intervals_;
  string s_;
  size_t s_len_{};

  void find_all_palindromic_substring_intervals() {
    palindromic_substring_intervals_.clear();
    min_number_of_registered_cuts_at_nodes_.clear();

    for (const auto& char_indices : char_positions_) {
      const vector<size_t>& char_offsets{char_indices.second};

      for (size_t i{}; i < char_offsets.size() - 1; ++i)
        for (size_t j{i + 1}; j < char_offsets.size(); ++j) {
          if (is_palindromic_substr(char_offsets[i], char_offsets[j] + 1))
            palindromic_substring_intervals_.emplace(char_offsets[i],
                                                     char_offsets[j]);
        }
    }

    currently_visited_palindromic_substring_intervals_.clear();
    currently_visited_palindromic_substring_intervals_.reserve(
        palindromic_substring_intervals_.size());
  }

  void update_currently_calculated_minimum_number_of_cuts_at_visited_nodes() {
    for (const palindromic_interval& pi :
         currently_visited_palindromic_substring_intervals_) {
      const auto found_iter{min_number_of_registered_cuts_at_nodes_.find(
          make_pair(pi.start, pi.last))};
      if (found_iter != end(min_number_of_registered_cuts_at_nodes_) &&
          pi.number_of_cuts >= found_iter->second)
        continue;
      min_number_of_registered_cuts_at_nodes_[make_pair(pi.start, pi.last)] =
          pi.number_of_cuts;
    }
  }

  void find_minimum_number_of_cuts(
      multimap<size_t, size_t>::iterator current,
      const multimap<size_t, size_t>::iterator& last,
      size_t& minimum_cuts,
      size_t current_number_of_cuts) {
    if (current_number_of_cuts >= minimum_cuts)
      return;

    while (current != last) {
      multimap<size_t, size_t>::iterator next{current};
      ++next;

      while (next != last && next->first > current->second) {
        current_number_of_cuts += next->first - current->second;
        if (current_number_of_cuts >= minimum_cuts)
          return;
        current = next;
        ++next;
      }

      if (last == next) {
        if (current_number_of_cuts + s_len_ - 1 - current->second <
            minimum_cuts) {
          minimum_cuts = current_number_of_cuts + s_len_ - 1 - current->second;
          update_currently_calculated_minimum_number_of_cuts_at_visited_nodes();
        }
        return;
      }

      const size_t last_interval_second{current->second};

      next = palindromic_substring_intervals_.upper_bound(last_interval_second);
      if (last == next) {
        if (current_number_of_cuts + s_len_ - 1 - last_interval_second <
            minimum_cuts) {
          minimum_cuts =
              current_number_of_cuts + s_len_ - 1 - last_interval_second;
          update_currently_calculated_minimum_number_of_cuts_at_visited_nodes();
        }
      } else {
        const auto found_iter{min_number_of_registered_cuts_at_nodes_.find(
            make_pair(next->first, next->second))};
        const size_t number_of_cuts_for_next_node{
            current_number_of_cuts + next->first - last_interval_second};
        if (found_iter != end(min_number_of_registered_cuts_at_nodes_) &&
            number_of_cuts_for_next_node >= found_iter->second)
          return;
        currently_visited_palindromic_substring_intervals_.emplace_back(
            next->first, next->second, number_of_cuts_for_next_node);
        find_minimum_number_of_cuts(next, last, minimum_cuts,
                                    number_of_cuts_for_next_node);
        currently_visited_palindromic_substring_intervals_.pop_back();
      }

      const size_t last_interval_first{current->first};

      ++current;
      if (last == current) {
        if (current_number_of_cuts + s_len_ - 1 - last_interval_second <
            minimum_cuts) {
          minimum_cuts =
              current_number_of_cuts + s_len_ - 1 - last_interval_second;
          update_currently_calculated_minimum_number_of_cuts_at_visited_nodes();
        }
        return;
      }

      if (next == current)
        return;
      current_number_of_cuts += current->first - last_interval_first;
    }
  }

  bool is_palindromic_substr(const size_t start, const size_t last) const {
    for (size_t i{start}, j{last - 1}; i < j; ++i, --j) {
      if (s_[i] != s_[j])
        return false;
    }

    return true;
  }

 public:
  size_t minCut(string s) {
    s_len = s_len_ = s.length();

    if (s_len_ < 2)
      return 0;

    s_ = move(s);

    if (s_.front() == s_.back() && is_palindromic_substr(0, s_len_))
      return 0;

    char_positions_.clear();

    for (size_t i{}; i < s_len_; ++i)
      char_positions_[s_[i]].emplace_back(i);

    find_all_palindromic_substring_intervals();

    size_t minimum_cuts{string::npos};
    if (palindromic_substring_intervals_.empty())
      return s_len_ - 1;

    const auto first_pi_iter{begin(palindromic_substring_intervals_)};

    find_minimum_number_of_cuts(first_pi_iter,
                                end(palindromic_substring_intervals_),
                                minimum_cuts, first_pi_iter->first);

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
       << '\n';  // expected output: 452

  cout << "s.minCut(\"abazcabacxy\") -> " << s.minCut(string{"abazcabacxy"})
       << '\n';  // expected output: 4

  cout << "s.minCut(\"eegiicgaeadbcfacfhifdbiehbgejcaeggcgbahfcajfhjjdgj\") "
          "-> "
       << s.minCut(string{"eegiicgaeadbcfacfhifdbiehbgejcaeggcgbahfcajfhjjdgj"})
       << '\n';  // expected output: 42

  cout << "s.minCut("
          "\"adabdcaebdcebdcacaaaadbbcadabcbeabaadcbcaaddebdbddcbdacdbbaedbdaae"
          "cabdceddccbdeeddccdaabbabbdedaaabcdadbdabeacbeadbaddcbaacdbabcccbace"
          "edbcccedbeecbccaecadccbdbdccbcbaacccbddcccbaedbacdbcaccdcaadcbaebebc"
          "ceabbdcdeaabdbabadeaaaaedbdbcebcbddebccacacddebecabccbbdcbecbaeedcda"
          "cdcbdbebbacddddaabaedabbaaabaddcdaadcccdeebcabacdadbaacdccbeceddeebb"
          "bdbaaaaabaeecccaebdeabddacbedededebdebabdbcbdcbadbeeceecdcdbbdcbdbee"
          "ebcdcabdeeacabdeaedebbcaacdadaecbccbededceceabdcabdeabbcdecdedadcaeb"
          "aababeedcaacdbdacbccdbcece\") -> "
       << s.minCut(string{
              "adabdcaebdcebdcacaaaadbbcadabcbeabaadcbcaaddebdbddcbdacdbbaedbda"
              "aecabdceddccbdeeddccdaabbabbdedaaabcdadbdabeacbeadbaddcbaacdbabc"
              "ccbaceedbcccedbeecbccaecadccbdbdccbcbaacccbddcccbaedbacdbcaccdca"
              "adcbaebebcceabbdcdeaabdbabadeaaaaedbdbcebcbddebccacacddebecabccb"
              "bdcbecbaeedcdacdcbdbebbacddddaabaedabbaaabaddcdaadcccdeebcabacda"
              "dbaacdccbeceddeebbbdbaaaaabaeecccaebdeabddacbedededebdebabdbcbdc"
              "badbeeceecdcdbbdcbdbeeebcdcabdeeacabdeaedebbcaacdadaecbccbededce"
              "ceabdcabdeabbcdecdedadcaebaababeedcaacdbdacbccdbcece"})
       << '\n';  // expected output: 276

  cout << "Elapsed time: " << Solution::start_stop_timer() << " seconds\n";

  return 0;
}
