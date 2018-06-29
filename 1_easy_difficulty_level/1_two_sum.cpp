/*
1. Leetcode coding challenge: Two sum

Given an array of integers, return indices of the two numbers such that they add
up to a specific target. You may assume that each input would have exactly one
solution, and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
*/

#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

static int sres = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

template <typename T>
void print_range(T&& first, T&& last, ostream& os) {
  if (first == last)
    return;
  --last;
  os << '[';
  for_each(first, last, [&os](const auto& data) { os << data << ','; });
  os << *last << "]\n";
}

class Solution {
 public:
  Solution() = default;
  vector<int> twoSum(vector<int>& nums, const int target) {
    unordered_multiset<int> nums_freq(begin(nums), end(nums));
    unordered_set<int> already_visited{};
    const int nums_size = nums.size();

    for (int i{}; i < nums_size - 1; i++) {
      if (already_visited.find(nums[i]) != end(already_visited))
        continue;

      already_visited.insert(nums[i]);

      const int second_number{target - nums[i]};

      if (nums_freq.find(second_number) == end(nums_freq))
        continue;

      if (nums[i] == second_number && nums_freq.count(nums[i]) < 2)
        continue;

      for (int j{i + 1}; j < nums_size; j++) {
        if (second_number == nums[j]) {
          return vector<int>{i, j};
        }
      }
    }

    return vector<int>{-1, -1};
  }
};

int main() {
  Solution s{};

  vector<int> input{2, 7, 11, 15};
  auto result = s.twoSum(input, 9);
  cout << "s.twoSum({2, 7, 11, 15}, 9) -> ";
  print_range(begin(result), end(result), cout);
  return 0;
}