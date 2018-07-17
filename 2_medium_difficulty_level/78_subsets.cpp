/*
Given a set of distinct integers, nums, return all possible subsets (the power
set).

Note: The solution set must not contain duplicate subsets.

Example:

Input: nums = [1,2,3,4]
Output:
[
  [],
  [1],
  [2],
  [3],
  [4],
  [1,2],
  [1,3],
  [1,4],
  [2,3],
  [2,4],
  [3,4],
  [1,2,3],
  [1,2,4],
  [1,3,4],
  [2,3,4],
  [1,2,3,4]
]
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

static int sr = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

template <typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& data) {
  if (data.empty()) {
    os << "\n{\n  [],\n}\n";
    return os;
  }
  os << "\n{\n";
  for (size_t i{}; i < data.size() - 1; i++) {
    if (0 == data[i].size()) {
      os << "  [],\n";
      continue;
    }
    os << "  [";
    for (size_t j{}; j < data[i].size() - 1; j++)
      os << data[i][j] << ',';
    os << data[i].back() << "],\n";
  }

  os << "  [";
  for (size_t j{}; j < data.back().size() - 1; j++)
    os << data.back()[j] << ',';
  os << data.back().back() << "]\n}\n";

  return os;
}

class Solution {
  static void generate_combinations_of_n_over_k(const vector<int>& nums,
                                                const size_t nums_size,
                                                const size_t k,
                                                vector<int>& set,
                                                vector<vector<int>>& result_set,
                                                const size_t start = 0,
                                                const size_t iter_count = 0) {
    if (iter_count == k) {
      result_set.emplace_back(set);
      return;
    }

    for (size_t i{start}; i <= min(start + nums_size - k, nums_size - 1); i++) {
      set[iter_count] = nums[i];
      generate_combinations_of_n_over_k(nums, nums_size, k, set, result_set,
                                        i + 1, iter_count + 1);
    }
  }

 public:
  vector<vector<int>> subsets(vector<int>& nums) {
    const size_t nums_size{nums.size()};
    if (!nums_size)
      return vector<vector<int>>{};
    if (1 == nums_size)
      return vector<vector<int>>{{}, {nums.front()}};

    vector<vector<int>> result_set{};
    result_set.reserve(static_cast<size_t>(pow(2u, nums_size)));
    result_set.emplace_back(vector<int>{});

    for (size_t k{1}; k <= nums_size - 1; k++) {
      vector<int> set(k);
      generate_combinations_of_n_over_k(nums, nums_size, k, set, result_set);
    }

    result_set.emplace_back(move(nums));

    return result_set;
  }
};

int main() {
  Solution s{};

  vector<int> input{1, 2, 3};

  vector<vector<int>> output{s.subsets(input)};
  cout << "s.subsets({1,2,3}) -> " << output << '\n';
  input.assign({1, 2, 3, 4});
  output = s.subsets(input);
  cout << "s.subsets({1,2,3,4}) -> " << output << '\n';

  return 0;
}
