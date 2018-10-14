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
                       const size_t number_of_cuts = 0)
      : start{start}, last{last}, number_of_cuts{number_of_cuts} {}
};

static size_t s_len;

namespace std {
template <>
struct hash<pair<size_t, size_t>> {
  size_t operator()(const pair<size_t, size_t>& p) const noexcept {
    return p.first * s_len + p.second;
  }
};
}  // namespace std

class Solution {
  unordered_map<char, vector<size_t>> char_positions_;
  multimap<size_t, size_t> palindromic_substring_intervals_;
  unordered_map<pair<size_t, size_t>, size_t>
      min_number_of_registered_cuts_at_nodes_;
  unordered_map<pair<size_t, size_t>, int>
      is_palindromic_substring_interval_overlapped_;
  vector<palindromic_interval> palindromic_intervals_;
  vector<palindromic_interval>
      currently_visited_palindromic_substring_intervals_;
  string s_;
  size_t s_len_{}, minimum_cuts{string::npos};
  multimap<size_t, size_t>::iterator last;

  bool find_overshadowed_shorter_palindromic_intervals(
      const palindromic_interval& pi,
      vector<pair<size_t, size_t>>& remove_palindromic_intervals) {
    bool is_found_overshadowed_palindromic_intervals{};
    for (const auto& p : palindromic_substring_intervals_) {
      if (p.first == pi.start && p.second == pi.last)
        continue;
      if ((p.first < pi.start && p.second >= pi.start && p.second <= pi.last) ||
          (p.first >= pi.start && p.first <= pi.last && p.second > pi.last))
        return false;
      if (pi.start <= p.first && pi.last >= p.second) {
        remove_palindromic_intervals.emplace_back(p.first, p.second);
        is_found_overshadowed_palindromic_intervals = true;
      }
    }

    is_palindromic_substring_interval_overlapped_[make_pair(pi.start,
                                                            pi.last)] = 0;
    return is_found_overshadowed_palindromic_intervals;
  }

  void find_all_palindromic_substring_intervals() {
    palindromic_substring_intervals_.clear();
    is_palindromic_substring_interval_overlapped_.clear();
    min_number_of_registered_cuts_at_nodes_.clear();
    palindromic_intervals_.clear();

    char_positions_.clear();
    for (size_t i{}; i < s_len_; ++i)
      char_positions_[s_[i]].emplace_back(i);

    for (const auto& char_indices : char_positions_) {
      const vector<size_t>& char_offsets{char_indices.second};
      for (size_t i{}; i < char_offsets.size() - 1; ++i) {
        for (size_t j{i + 1}; j < char_offsets.size(); ++j) {
          if (is_palindromic_substr(char_offsets[i], char_offsets[j] + 1)) {
            palindromic_substring_intervals_.emplace(char_offsets[i],
                                                     char_offsets[j]);
            is_palindromic_substring_interval_overlapped_[make_pair(
                char_offsets[i], char_offsets[j])] = 1;
            palindromic_intervals_.emplace_back(char_offsets[i],
                                                char_offsets[j]);
          }
        }
      }
    }

    sort(begin(palindromic_intervals_), end(palindromic_intervals_),
         [](const palindromic_interval& lhs, const palindromic_interval& rhs) {
           return lhs.last - lhs.start > rhs.last - rhs.start;
         });
    for (const auto& pi : palindromic_intervals_) {
      if (is_palindromic_substring_interval_overlapped_.find(
              make_pair(pi.start, pi.last)) ==
          end(is_palindromic_substring_interval_overlapped_))
        continue;
      vector<pair<size_t, size_t>> remove_palindromic_intervals{};
      if (find_overshadowed_shorter_palindromic_intervals(
              pi, remove_palindromic_intervals)) {
        for (const pair<size_t, size_t>& rpi : remove_palindromic_intervals) {
          for (auto current{
                   palindromic_substring_intervals_.lower_bound(rpi.first)};
               current !=
               palindromic_substring_intervals_.upper_bound(rpi.first);
               ++current) {
            if (rpi.second == current->second) {
              palindromic_substring_intervals_.erase(current);
              is_palindromic_substring_interval_overlapped_.erase(
                  make_pair(rpi.first, rpi.second));
              break;
            }
          }
        }
      }
    }

    currently_visited_palindromic_substring_intervals_.clear();
    currently_visited_palindromic_substring_intervals_.reserve(
        palindromic_substring_intervals_.size());
  }

  void update_currently_calculated_minimum_number_of_cuts_at_visited_nodes() {
    unordered_map<pair<size_t, size_t>, size_t>
        current_number_of_registered_cuts_at_nodes{};

    for (const palindromic_interval& pi :
         currently_visited_palindromic_substring_intervals_)
      current_number_of_registered_cuts_at_nodes[make_pair(pi.start, pi.last)] =
          pi.number_of_cuts;

    min_number_of_registered_cuts_at_nodes_.swap(
        current_number_of_registered_cuts_at_nodes);
  }

  void find_minimum_number_of_cuts(multimap<size_t, size_t>::iterator current,
                                   size_t current_number_of_cuts) {
    while (current != last) {
      multimap<size_t, size_t>::iterator next{current};
      ++next;

      while (next != last && next->first > current->second) {
        current_number_of_cuts += next->first - current->second;
        if (current_number_of_cuts >= minimum_cuts)
          return;
        const auto found_iter{min_number_of_registered_cuts_at_nodes_.find(
            make_pair(current->first, current->second))};
        if (found_iter != end(min_number_of_registered_cuts_at_nodes_) &&
            current_number_of_cuts >= found_iter->second)
          return;
        currently_visited_palindromic_substring_intervals_.emplace_back(
            current->first, current->second, current_number_of_cuts);
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
      } else
        find_minimum_number_of_cuts(
            next, current_number_of_cuts + next->first - last_interval_second);

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

  bool is_palindromic_substr(const size_t start_pos,
                             const size_t last_pos) const {
    for (size_t i{start_pos}, j{last_pos - 1}; i < j; ++i, --j) {
      if (s_[i] != s_[j])
        return false;
    }

    return true;
  }

  bool
  check_if_whole_input_string_is_comprised_of_palindromic_substr_intervals() {
    size_t i{}, j{s_len_}, pi_count{};
    while (j - i > 1) {
      if (is_palindromic_substr(i, j)) {
        pi_count++;
        if (s_len_ == j) {
          minimum_cuts = pi_count - 1;
          return true;
        }
        i = j;
        j = s_len_;
        continue;
      }

      j--;
    }

    return false;
  }

 public:
  size_t minCut(string s) {
    s_len = s_len_ = s.length();

    if (s_len_ < 2)
      return 0;

    s_ = move(s);

    if (check_if_whole_input_string_is_comprised_of_palindromic_substr_intervals())
      return minimum_cuts;

    find_all_palindromic_substring_intervals();

    if (palindromic_substring_intervals_.empty())
      return s_len_ - 1;

    minimum_cuts = string::npos;
    last = end(palindromic_substring_intervals_);

    const auto first_pi_iter{begin(palindromic_substring_intervals_)};

    find_minimum_number_of_cuts(first_pi_iter, first_pi_iter->first);

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
          "\"adabdcaebdcebdcacaaaadbbcadabcbeabaadcbcaaddebdbddcbdacdbbaedbda"
          "ae"
          "cabdceddccbdeeddccdaabbabbdedaaabcdadbdabeacbeadbaddcbaacdbabcccba"
          "ce"
          "edbcccedbeecbccaecadccbdbdccbcbaacccbddcccbaedbacdbcaccdcaadcbaebe"
          "bc"
          "ceabbdcdeaabdbabadeaaaaedbdbcebcbddebccacacddebecabccbbdcbecbaeedc"
          "da"
          "cdcbdbebbacddddaabaedabbaaabaddcdaadcccdeebcabacdadbaacdccbeceddee"
          "bb"
          "bdbaaaaabaeecccaebdeabddacbedededebdebabdbcbdcbadbeeceecdcdbbdcbdb"
          "ee"
          "ebcdcabdeeacabdeaedebbcaacdadaecbccbededceceabdcabdeabbcdecdedadca"
          "eb"
          "aababeedcaacdbdacbccdbcece\") -> "
       << s.minCut(
              string{"adabdcaebdcebdcacaaaadbbcadabcbeabaadcbcaaddebdbddcbdac"
                     "dbbaedbda"
                     "aecabdceddccbdeeddccdaabbabbdedaaabcdadbdabeacbeadbaddc"
                     "baacdbabc"
                     "ccbaceedbcccedbeecbccaecadccbdbdccbcbaacccbddcccbaedbac"
                     "dbcaccdca"
                     "adcbaebebcceabbdcdeaabdbabadeaaaaedbdbcebcbddebccacacdd"
                     "ebecabccb"
                     "bdcbecbaeedcdacdcbdbebbacddddaabaedabbaaabaddcdaadcccde"
                     "ebcabacda"
                     "dbaacdccbeceddeebbbdbaaaaabaeecccaebdeabddacbedededebde"
                     "babdbcbdc"
                     "badbeeceecdcdbbdcbdbeeebcdcabdeeacabdeaedebbcaacdadaecb"
                     "ccbededce"
                     "ceabdcabdeabbcdecdedadcaebaababeedcaacdbdacbccdbcece"})
       << '\n';  // expected output: 276

  cout << "s.minCut("
          "\"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbaaaaaaaaaaaaaaaaaaaaaaaa"
          "aa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\") -> "
       << s.minCut(string{
              "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
              "aa"
              "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
              "aa"
              "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
              "aa"
              "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
              "aa"
              "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
              "aa"
              "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
              "aa"
              "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
              "aa"
              "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
              "aa"
              "aabbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
              "aa"
              "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
              "aa"
              "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
              "aa"
              "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
              "aa"
              "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
              "aa"
              "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
              "aa"
              "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
              "aa"
              "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
              "aa"
              "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
              "aa"
              "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
              "aa"
              "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
              "aa"
              "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
              "aa"
              "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
              "aa"
              "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
              "aa"
              "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"})
       << '\n';  // expected output: 0

  cout << "Elapsed time: " << Solution::start_stop_timer() << " seconds\n";

  return 0;
}
