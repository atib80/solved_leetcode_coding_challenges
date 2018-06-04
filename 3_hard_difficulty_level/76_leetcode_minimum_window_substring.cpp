#include <algorithm>
#include <cctype>
#include <deque>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
 public:
  string minWindow_v1(string s, string t) {
    const size_t src_len{s.length()};
    const size_t needle_len{t.length()};

    if (string::npos != s.find(t))
      return t;

    size_t start_pos{s.find_first_of(t)};

    if (string::npos == start_pos)
      return "";
    else if (1 == needle_len)
      return t;

    unordered_map<char, int> needle_char_count{};
    for_each(begin(t), end(t), [&](const char ch) { needle_char_count[ch]++; });

    unordered_map<char, int> current_substr_char_count{};
    for (const pair<char, int>& p : needle_char_count) {
      current_substr_char_count.insert(make_pair(p.first, 0));
    }

    size_t min_substr_len{string::npos};
    string min_substr{};
    deque<pair<size_t, char>> current_substr_chars{
        {make_pair(start_pos, s[start_pos])}};
    current_substr_char_count[s[start_pos]]++;

    while ((start_pos = s.find_first_of(t, start_pos + 1)) != string::npos) {
      current_substr_char_count[s[start_pos]]++;
      current_substr_chars.emplace_back(make_pair(start_pos, s[start_pos]));
      if (current_substr_chars.size() >= needle_len) {
        while (current_substr_chars.size() > needle_len) {
          const char ch_index{current_substr_chars.front().second};
          if (current_substr_char_count[ch_index] >
              needle_char_count[ch_index]) {
            current_substr_char_count[ch_index]--;
            current_substr_chars.pop_front();
          } else
            break;
        }

        size_t substr_len{current_substr_chars.back().first -
                          current_substr_chars.front().first + 1};
        while (substr_len >= min_substr_len) {
          current_substr_char_count[current_substr_chars.front().second]--;
          current_substr_chars.pop_front();
          substr_len = current_substr_chars.back().first -
                       current_substr_chars.front().first + 1;
        }

        bool found_min_window_substr{true};
        for (const pair<char, int>& p : needle_char_count) {
          if (current_substr_char_count[p.first] < p.second) {
            found_min_window_substr = false;
            break;
          }
        }

        if (found_min_window_substr) {
          min_substr_len = substr_len;
          min_substr = s.substr(current_substr_chars.front().first, substr_len);
        }
      }
    }

    return min_substr;
  }

  string minWindow_v2(string s, string t) {
    int s_char_count[128]{}, t_char_count[128]{};
    const size_t s_len{s.length()}, t_len{t.length()};
    size_t count{}, minWinLen{s.size()}, startPos{}, i{};
    bool isComplete{};
    for (const char c : t)
      t_char_count[c]++;

    for (size_t j{}; j < s_len; j++) {
      const char c{s[j]};
      if (!t_char_count[c])
        continue;

      if (s_char_count[c] < t_char_count[c]) {
        count++;
        if (t_len == count)
          isComplete = true;
      }

      s_char_count[c]++;

      while (i < j) {
        if (!t_char_count[s[i]])
          i++;
        else if (s_char_count[s[i]] > t_char_count[s[i]]) {
          s_char_count[s[i]]--;
          i++;
        } else
          break;
      }

      if (isComplete && j - i + 1 < minWinLen) {
        minWinLen = j - i + 1;
        startPos = i;
      }
    }

    return isComplete ? s.substr(startPos, minWinLen) : "";
  }
};

int main() {
  Solution s{};
  cout << "s.minWindow_v1(string{\"ADOBECODEBANC\"}, string{\"ABC\"}) -> "
       << s.minWindow_v1(string{"ADOBECODEBANC"}, string{"ABC"})
       << '\n';  // expected output: "BANC"

  cout << "s.minWindow_v1(string{\"bba\"}, string{\"ab\"}) -> "
       << s.minWindow_v1(string{"bba"}, string{"ab"})
       << '\n';  // expected output: "ba"
  return 0;
}
