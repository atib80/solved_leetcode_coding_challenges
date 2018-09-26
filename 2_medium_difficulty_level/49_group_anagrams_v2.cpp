/*
49. Leetcode coding challenge: Group anagrams (difficulty level: medium)

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

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& data) {
  if (data.empty()) {
    os << "data is empty\n";
    return os;
  }
  os << "\n  [";
  for (size_t i{}; i < data.size() - 1; i++)
    os << data[i] << ',';
  os << data.back() << ']';
  return os;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& data) {
  if (data.empty()) {
    os << "data is empty\n";
    return os;
  }

  os << "\n[\n";
  for (const auto& row : data)
    os << row;
  os << "\n]\n";

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
        empty_words.emplace_back("");
      else {
        string anagram_key{strs[i]};
        sort(begin(anagram_key), end(anagram_key));
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
  cout << "s.groupAnagrams({eat, tea, tan, ate, nat, bat}) -> " << result
       << '\n';

  return 0;
}
