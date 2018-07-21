/*
90. Leetcode coding challenge: Subsets II

Given a collection of integers that might contain duplicates, nums, return all
possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

Example:

Input: [1,2,2]
Output:
[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& data) {
  if (data.empty()) {
    os << "\n  []";
    return os;
  }
  os << "\n  [";
  for (size_t i{}; i < data.size() - 1; i++)
    os << data[i] << ',';
  os << data.back() << "]";
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
  string hash_index;

  static size_t max(const size_t x, const size_t y) { return x > y ? x : y; }

  void generate_unique_hash_index(const vector<int>& set) {
    hash_index.clear();
    for (int number : set) {
      if (!number)
        hash_index.push_back('0');
      else {
        if (number < 0)
          hash_index.push_back('-');
        while (number) {
          hash_index.push_back(static_cast<char>('0' + number % 10));
          number /= 10;
        }
      }
      hash_index.push_back('.');
    }

    hash_index.pop_back();
  }

 public:
  vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    const size_t nums_size{nums.size()};
    if (!nums_size)
      return vector<vector<int>>{};
    if (1 == nums_size)
      return vector<vector<int>>{{}, {nums.front()}};

    vector<vector<int>> result_set{};
    result_set.reserve(1 << nums_size);
    result_set.emplace_back(vector<int>{});

    unordered_set<string> unique_sets{};
    hash_index.reserve(1024);
    sort(begin(nums), end(nums));

    for (size_t k{1}; k <= nums_size; k++) {
      vector<int> set(k, 0);
      vector<size_t> indices(k);

      size_t rep{nums_size};
      for (size_t i{nums_size - 1}; i > max(1u, nums_size - k); i--)
        rep *= i;
      size_t divisor{k};
      for (size_t i{k - 1}; i > 1; i--)
        divisor *= i;
      rep /= divisor;

      for (size_t i{}; i < k; i++)
        indices[i] = i;

      for (size_t c{}; c < rep; c++) {
        for (size_t i{}; i < indices.size(); i++)
          set[i] = nums[indices[i]];

        generate_unique_hash_index(set);
        if (!unique_sets.count(hash_index)) {
          result_set.emplace_back(set);
          unique_sets.insert(hash_index);
        }

        bool carry{};

        // shift indices one at a time according to their currently set
        // positions if an index reaches its maximum allowed position, increase
        // the value of the previous index and reset all the following indices
        // to their new initial positions

        for (int i = k - 1, offset{}; i >= 0; i--, offset++) {
          if (!i && indices[i] > nums_size - k)
            break;
          if (nums_size - 1 - offset == indices[i]) {
            carry = true;
            continue;
          }

          indices[i]++;
          if (carry) {
            for (size_t x = i + 1; x < k; x++)
              indices[x] = indices[x - 1] + 1;
          }
          break;
        }
      }
    }

    return result_set;
  }
};

int main() {
  Solution s{};

  vector<int> input{1, 2, 2};
  auto output = s.subsetsWithDup(input);
  cout << "s.subsetsWithDup({1, 2, 2}) -> " << output << '\n';

  input.assign({9, 0, 3, 5, 7});
  output = s.subsetsWithDup(input);
  cout << "s.subsetsWithDup({9,0,3,5,7}) -> " << output << '\n';

  input.assign({1, 9, 8, 3, -1, 0});
  output = s.subsetsWithDup(input);
  cout << "s.subsetsWithDup({1,9,8,3,-1,0}) -> " << output << '\n';

  return 0;
}