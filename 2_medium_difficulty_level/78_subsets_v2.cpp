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

  if (0 == data.back().size())
    os << "  []\n}\n";
  else {
    os << "  [";
    for (size_t j{}; j < data.back().size() - 1; j++)
      os << data.back()[j] << ',';
    os << data.back().back() << "]\n}\n";
  }

  return os;
}

class Solution {
  static size_t max(const size_t x, const size_t y) { return x > y ? x : y; }

 public:
  vector<vector<int>> subsets(vector<int>& nums) {
    const size_t nums_size{nums.size()};
    if (!nums_size)
      return vector<vector<int>>{};
    if (1 == nums_size)
      return vector<vector<int>>{{}, {nums.front()}};

    vector<vector<int>> result_set{};
    result_set.reserve(1 << nums_size);
    result_set.emplace_back(vector<int>{});

    sort(begin(nums), end(nums));

    for (size_t k{1}; k <= nums_size; k++) {
      vector<int> set(k);
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
        result_set.emplace_back(set);

        bool carry{};

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

  vector<int> input{1, 2, 3};

  vector<vector<int>> output{s.subsets(input)};
  cout << "s.subsets({1,2,3}) -> " << output << '\n';
  input.assign({1, 2, 3, 4});
  output = s.subsets(input);
  cout << "s.subsets({1,2,3,4}) -> " << output << '\n';
  input.assign({9, 0, 3, 5, 7});
  output = s.subsets(input);
  cout << "s.subsets({9,0,3,5,7}) -> " << output << '\n';

  /*
  Input: [9,0,3,5,7]
Output:
[[],[0],[3],[5],[7],[9],[0,3],[0,5],[0,7],[0,9],[3,5],[3,7],[3,9],[5,7],[5,9],[7,9],[0,3,5],[0,3,7],[0,3,9],[0,5,7],
           [0,5,9],[0,7,9],[3,5,9],[3,7,9],[5,7,9],[3,7,9],[0,3,5,7],[0,3,5,9],[0,3,7,9],[0,5,7,9],[3,5,7,9],[0,3,5,7,9]]

Expected:
[[],[9],[0],[0,9],[3],[3,9],[0,3],[0,3,9],[5],[5,9],[0,5],[0,5,9],[3,5],[3,5,9],[0,3,5],[0,3,5,9],[7],[7,9],[0,7],
           [0,7,9],[3,7],[3,7,9],[0,3,7],[0,3,7,9],[5,7],[5,7,9],[0,5,7],[0,5,7,9],[3,5,7],[3,5,7,9],[0,3,5,7],[0,3,5,7,9]]
  */

  return 0;
}
