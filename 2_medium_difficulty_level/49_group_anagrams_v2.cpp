/*

49. leetcode coding challenge: Group Anagrams

Given an array of strings, group anagrams together.

Example:

Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
Output:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]

Note:

    All inputs will be in lowercase.
    The order of your output does not matter.

*/

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

static int sres = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  return 0;
}();

using std::cout;
using std::ostream;
using std::pair;
using std::sort;
using std::string;
using std::unordered_map;
using std::vector;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& data) {
  if (data.empty()) {
    os << "data is empty\n";
    return os;
  }
  os << "\n[";
  for (size_t i{}; i < data.size() - 1; i++)
    os << data[i] << ',';
  os << data.back() << "]\n";
  return os;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& data) {
  if (data.empty()) {
    os << "data is empty\n";
    return os;
  }
  os << "\n[\n";
  for (size_t i{}; i < data.size() - 1; i++) {
    os << "  [";
    for (size_t j{}; j < data[i].size() - 1; j++)
      os << data[i][j] << ',';
    os << data[i].back() << "],\n";
  }

  os << "  [";
  for (size_t j{}; j < data.back().size() - 1; j++)
    os << data.back()[j] << ',';
  os << data.back().back() << "]\n]\n";

  return os;
}

class Solution {
 public:
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<vector<string>> output{};
    const size_t words_size{strs.size()};
    if (!words_size)
      return output;

    unordered_map<string, vector<string>> anagram_dict{};
    vector<string> empty_words{};

    for (size_t i{}; i < words_size; i++) {
      if (strs[i].empty())
        empty_words.emplace_back(move(strs[i]));
      else {
        string anagram_key{strs[i]};

        sort(begin(anagram_key), end(anagram_key));
        if (anagram_dict.find(anagram_key) == end(anagram_dict))
          anagram_dict.insert(
              make_pair(anagram_key, vector<string>{move(strs[i])}));
        else
          anagram_dict[anagram_key].emplace_back(move(strs[i]));
      }
    }

    if (!empty_words.empty())
      output.emplace_back(move(empty_words));

    for (pair<const string, vector<string>>& anagram_words : anagram_dict)
      output.emplace_back(move(anagram_words.second));

    return output;
  }
};

int main() {
  Solution s{};

  vector<string> input{"eat", "tea", "tan", "ate", "nat", "bat"};

  vector<vector<string>> result{s.groupAnagrams(input)};

  cout << "s.groupAnagrams({ \"eat\", \"tea\", \"tan\", \"ate\", \"nat\", "
          "\"bat\"}) -> "
       << result << '\n';

  return 0;
}

https://www.redtube.com/?search=gemma+massey