/*
216. Combination sum III (difficulty level: medium)

Find all possible combinations of k numbers that add up to a number n, given
that only numbers from 1 to 9 can be used and each combination should be a
unique set of numbers.

Note:

    All numbers will be positive integers.
    The solution set must not contain duplicate combinations.

Example 1:

Input:  k = 3, n = 7
Output: [[1,2,4]]

Example 2:

Input:  k = 3, n = 9
Output: [[1,2,6], [1,3,5], [2,3,4]]
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& data) {
  if (data.empty()) {
    os << "data is empty\n";
    return os;
  }
  os << '[';
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

  os << '[';
  for (size_t i{}; i < data.size() - 1; ++i)
    os << data[i] << ',';
  os << data.back() << ']';

  return os;
}

class Solution {
  void generate_unique_combinations(const int n,
                                    const int k,
                                    int current_number,
                                    vector<int>& unique_combination,
                                    vector<vector<int>>& combinations,
                                    const int current_sum = 0,
                                    const int iter_count = 0) {
    while (current_number <= 9 - (k - iter_count) + 1) {
      if (iter_count + 1 == k) {
        if (current_sum + current_number == n) {
          unique_combination[iter_count] = current_number;
          combinations.emplace_back(unique_combination);
          return;
        } else if (current_sum + current_number > n)
          return;

      } else if (current_sum + current_number < n) {
        unique_combination[iter_count] = current_number;
        generate_unique_combinations(
            n, k, current_number + 1, unique_combination, combinations,
            current_sum + current_number, iter_count + 1);
      }
      current_number++;
    }
  }

 public:
  vector<vector<int>> combinationSum3(const int k, const int n) {
    vector<vector<int>> unique_combinations_for_sum_n{};
    if (!k || !n)
      return unique_combinations_for_sum_n;
    if (1 == n) {
      if (1 == k)
        return {{1}};
      return unique_combinations_for_sum_n;
    }

    vector<int> unique_combination(k, 0);

    generate_unique_combinations(n, k, 1, unique_combination,
                                 unique_combinations_for_sum_n);

    return unique_combinations_for_sum_n;
  }
};

int main() {
  Solution s{};

  vector<vector<int>> unique_combinations{s.combinationSum3(3, 7)};
  cout << "s.combinationSum3(3, 7) -> " << unique_combinations
       << '\n';  // expected  output: [[1,2,4]]
  unique_combinations = s.combinationSum3(3, 9);
  cout << "s.combinationSum3(3, 9) -> " << unique_combinations
       << '\n';  // exoected output: [[1,2,6], [1,3,5], [2,3,4]]

  return 0;
}
