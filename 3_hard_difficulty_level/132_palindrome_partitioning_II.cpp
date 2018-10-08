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
#include <map>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const size_t max_string_length{string::npos};

template <typename CharacterPointerType,
          typename CheckConditionTypeParam = enable_if<
              is_same_v<remove_cv_t<CharacterPointerType>, char*> ||
                  is_same_v<remove_cv_t<CharacterPointerType>, wchar_t*> ||
                  is_same_v<remove_cv_t<CharacterPointerType>, char16_t*> ||
                  is_same_v<remove_cv_t<CharacterPointerType>, char32_t*>,
              void*>>

size_t str_length(CharacterPointerType src,
                  const size_t max_allowed_string_length = max_string_length) {
  if (!src || !*src)
    return 0u;

  size_t length{};

  while (*src++) {
    ++length;

    if (max_allowed_string_length == length)
      return max_allowed_string_length;
  }

  return length;
}

class Solution {
  unordered_map<char, vector<size_t>> char_positions_;
  multimap<size_t, size_t> palindromic_substring_intervals_;
  unordered_set<string> already_visited_palindromic_intervals_;
  string visited_palindromic_intervals_;
  string s_;
  size_t s_len_{};

  void find_all_palindromic_substring_intervals() {
    palindromic_substring_intervals_.clear();

    for (const auto& char_indices : char_positions_) {
      const vector<size_t>& char_offsets{char_indices.second};

      for (size_t i{}; i < char_offsets.size() - 1; ++i)
        for (size_t j{i + 1}; j < char_offsets.size(); ++j)
          if (is_palindromic_substr(char_offsets[i], char_offsets[j] + 1))
            palindromic_substring_intervals_.emplace(char_offsets[i],
                                                     char_offsets[j]);
    }
  }

  void find_minimum_number_of_cuts(
      multimap<size_t, size_t>::iterator current_palindromic_interval,
      const multimap<size_t, size_t>::iterator& last_palindromic_interval,
      size_t& minimum_cuts,
      size_t current_number_of_cuts) {
    while (current_palindromic_interval != last_palindromic_interval) {
      const multimap<size_t, size_t>::iterator next_palindromic_interval{
          palindromic_substring_intervals_.upper_bound(
              current_palindromic_interval->second)};

      if (next_palindromic_interval == last_palindromic_interval) {
        if (current_number_of_cuts + s_len_ - 1 -
                current_palindromic_interval->second <
            minimum_cuts)
          minimum_cuts = current_number_of_cuts + s_len_ - 1 -
                         current_palindromic_interval->second;
        return;
      }

      if (current_number_of_cuts + next_palindromic_interval->first -
              current_palindromic_interval->second <
          minimum_cuts)
        find_minimum_number_of_cuts(
            next_palindromic_interval, last_palindromic_interval, minimum_cuts,
            current_number_of_cuts + next_palindromic_interval->first -
                current_palindromic_interval->second);

      ++current_palindromic_interval;
      if (current_palindromic_interval != last_palindromic_interval) {
        current_number_of_cuts +=
            current_palindromic_interval->first - current_number_of_cuts;
        while (visited_palindromic_intervals_.back() != ',')
          visited_palindromic_intervals_.pop_back();

        visited_palindromic_intervals_.append(
            to_string(current_palindromic_interval->first));
        visited_palindromic_intervals_.push_back('-');
        visited_palindromic_intervals_.append(
            to_string(current_palindromic_interval->second));

        if (already_visited_palindromic_intervals_.find(
                visited_palindromic_intervals_) !=
            end(already_visited_palindromic_intervals_))
          return;

        already_visited_palindromic_intervals_.emplace(
            visited_palindromic_intervals_);
      }

      if (current_number_of_cuts >= minimum_cuts)
        return;
    }
  }

  bool is_palindromic_substr(const size_t start, const size_t last) {
    for (size_t i{start + 1}, j{last - 2}; i < j; i++, j--) {
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

    if (s_.front() == s_.back() && is_palindromic_substr(0, s_len_))
      return 0;

    char_positions_.clear();

    for (size_t i{}; i < s_len_; ++i)
      char_positions_[s_[i]].emplace_back(i);

    find_all_palindromic_substring_intervals();

    size_t minimum_cuts{string::npos};
    if (palindromic_substring_intervals_.empty())
      return s_len_ - 1;
    const auto first_palindromic_interval{
        begin(palindromic_substring_intervals_)};
    visited_palindromic_intervals_.clear();
    visited_palindromic_intervals_.reserve(1024);
    visited_palindromic_intervals_.push_back(',');
    visited_palindromic_intervals_.append(
        to_string(first_palindromic_interval->first));
    visited_palindromic_intervals_.push_back('-');
    visited_palindromic_intervals_.append(
        to_string(first_palindromic_interval->second));
    already_visited_palindromic_intervals_.clear();
    already_visited_palindromic_intervals_.emplace(
        visited_palindromic_intervals_);
    find_minimum_number_of_cuts(
        first_palindromic_interval, end(palindromic_substring_intervals_),
        minimum_cuts, first_palindromic_interval->first);
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

  // const char* src{"apple pie"};
  // cout << str_length(src) << '\n';

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

  cout << "s.minCut(\"abazcabacxy\") -> " << s.minCut(string{"abazcabacxy"})
       << '\n';  // expected output: 4

  cout << "Elapsed time: " << Solution::start_stop_timer() << " seconds\n";

  return 0;
}
