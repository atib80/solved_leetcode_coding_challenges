/*
77. Leetcode coding challenge: Combinations

Given two integers n and k, return all possible combinations of k numbers out of
1 ... n.

Example:

Input: n = 4, k = 2
Output:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
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
  static void generate_combinations_of_n_over_k(const int n,
                                                const int k,
                                                vector<int>& set,
                                                vector<vector<int>>& result_set,
                                                const int start = 0,
                                                const int iter_count = 0) {
    if (iter_count == k) {
      result_set.emplace_back(set);
      return;
    }

    for (int i{start}; i <= min(start + n - k, n - 1); i++) {
      set[iter_count] = i + 1;
      generate_combinations_of_n_over_k(n, k, set, result_set, i + 1,
                                        iter_count + 1);
    }
  }

 public:
  vector<vector<int>> combine(const int n, const int k) {
    if (!k || k > n)
      return vector<vector<int>>{};
    if (n < 2)
      vector<vector<int>>{{1}};
    if (n == k) {
      vector<int> set(n);
      for (int i{1}; i <= n; i++)
        set[i - 1] = i;
      return vector<vector<int>>{move(set)};
    }

    int initial_capacity{n};
    for (int i{n - 1}; i > max(1, n - k); i--)
      initial_capacity *= i;
    int divisor{k};
    for (int i{k - 1}; i > 1; i--)
      divisor *= i;
    initial_capacity /= divisor;
    vector<vector<int>> result_set{};
    result_set.reserve(initial_capacity);

    vector<int> set(k);
    generate_combinations_of_n_over_k(n, k, set, result_set);

    return result_set;
  }
};

int main() {
  Solution s{};

  vector<vector<int>> output{s.combine(4, 2)};
  cout << "s.combine(4, 2) -> " << output << '\n';
  output = s.combine(4, 3);
  cout << "s.combine(4, 3) -> " << output << '\n';
  output = s.combine(5, 3);
  cout << "s.combine(5, 3) -> " << output << '\n';
  output = s.combine(2, 2);
  cout << "s.combine(2, 2) -> " << output << '\n';
  output = s.combine(2, 1);
  cout << "s.combine(2, 1) -> " << output << '\n';
  output = s.combine(2, 0);
  cout << "s.combine(2, 0) -> " << output << '\n';
  output = s.combine(1, 1);
  cout << "s.combine(1, 1) -> " << output << '\n';
  output = s.combine(1, 0);
  cout << "s.combine(1, 0) -> " << output << '\n';
  output = s.combine(4, 5);
  cout << "s.combine(4, 5) -> " << output << '\n';
  output = s.combine(5, 2);
  cout << "s.combine(5, 2) -> " << output << '\n';

  return 0;
}
