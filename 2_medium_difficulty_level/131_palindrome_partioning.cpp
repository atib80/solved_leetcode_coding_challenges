/*
131. Palindrome partitioning (difficulty level: medium)

Given a string s, partition s such that every substring of the partition is a
palindrome.

Return all possible palindrome partitioning of s.

Example:

Input: "aab"
Output:
[
  ["aa","b"],
  ["a","a","b"]
]
*/

#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
void print_range(T&& first, T&& last, ostream& os) {
  if (first == last)
    return;
  --last;
  os << '[';
  for_each(forward<T>(first), forward<T>(last),
           [&os](const auto& data) { os << data << ','; });
  os << *last << "]\n";
}

template <typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& data) {
  if (data.empty()) {
    os << "data is empty\n";
    return os;
  }

  os << "\n[\n";
  for (const auto& row : data)
    print_range(cbegin(row), cend(row), os);
  os << "]\n";

  return os;
}

class Solution {
  vector<vector<string>> output_;
  vector<string> current_sequence_;
  string s_;
  size_t s_len_{};

  void find_all_palindrome_partitions(const size_t start_pos) {
    if (start_pos == s_len_) {
      output_.emplace_back(current_sequence_);
      return;
    }

    for (size_t last_pos{start_pos + 1}; last_pos <= s_len_; ++last_pos) {
      if (is_palindromic_substr(start_pos, last_pos)) {
        current_sequence_.push_back(s_.substr(start_pos, last_pos - start_pos));
        find_all_palindrome_partitions(last_pos);
        current_sequence_.pop_back();
      }
    }
  }

  bool is_palindromic_substr(const size_t start, const size_t last) const {
    for (size_t i{start}, j{last - 1}; i < j; i++, j--) {
      if (s_[i] != s_[j])
        return false;
    }

    return true;
  }

 public:
  vector<vector<string>> partition(string s) {
    s_len_ = s.length();

    if (!s_len_)
      return {};
    if (1 == s_len_)
      return {{move(s)}};

    s_ = move(s);
    current_sequence_.clear();
    current_sequence_.reserve(s_len_);
    output_.clear();
    find_all_palindrome_partitions(0);
    return move(output_);
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

  const vector<vector<string>> output1{s.partition(string{"aab"})};

  cout << "s.partition(\"aab\") -> " << output1
       << '\n';  // expected output: [["aa","b"], ["a","a","b"]]

  const vector<vector<string>> output2{s.partition(string{"a"})};

  cout << "s.partition(\"a\") -> " << output2
       << '\n';  // expected output: [["a"]]

  const vector<vector<string>> output3{s.partition(
      string{"apjesgpsxoeiokmqmfgvjslcjukbqxpsobyhjpbgdfruqdkeiszrlmtwgfxyfost"
             "pqczidfljwfbbrflkgdvtytbgqalguewnhvvmcgxboycffopmtmhtfizxkmeftcu"
             "cxpobxmelmjtuzigsxnncxpaibgpuijwhankxbplpyejxmrrjgeoevqozwdtgosp"
             "ohznkoyzocjlracchjqnggbfeebmuvbicbvmpuleywrpzwsihivnrwtxcukwplgt"
             "obhgxukwrdlszfaiqxwjvrgxnsveedxseeyeykarqnjrtlaliyudpacctzizcftj"
             "lunlgnfwcqqxcqikocqffsjyurzwysfjmswvhbrmshjuzsgpwyubtfbnwajuvrfh"
             "lccvfwhxfqthkcwhatktymgxostjlztwdxritygbrbibdgkezvzajizxasjnrcjw"
             "zdfvdnwwqeyumkamhzoqhnqjfzwzbixclcxqrtniznemxeahfozp"})};

  cout << "s.partition("
          "\"apjesgpsxoeiokmqmfgvjslcjukbqxpsobyhjpbgdfruqdkeiszrlmtwgfxyfostpq"
          "czidfljwfbbrflkgdvtytbgqalguewnhvvmcgxboycffopmtmhtfizxkmeftcucxpobx"
          "melmjtuzigsxnncxpaibgpuijwhankxbplpyejxmrrjgeoevqozwdtgospohznkoyzoc"
          "jlracchjqnggbfeebmuvbicbvmpuleywrpzwsihivnrwtxcukwplgtobhgxukwrdlszf"
          "aiqxwjvrgxnsveedxseeyeykarqnjrtlaliyudpacctzizcftjlunlgnfwcqqxcqikoc"
          "qffsjyurzwysfjmswvhbrmshjuzsgpwyubtfbnwajuvrfhlccvfwhxfqthkcwhatktym"
          "gxostjlztwdxritygbrbibdgkezvzajizxasjnrcjwzdfvdnwwqeyumkamhzoqhnqjfz"
          "wzbixclcxqrtniznemxeahfozp\") -> "
       << output3 << '\n';

  cout << "Elapsed time: " << Solution::start_stop_timer() << " seconds\n";

  return 0;
}
