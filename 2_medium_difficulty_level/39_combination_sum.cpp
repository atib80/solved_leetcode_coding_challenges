/*
Leetcode coding challenge: Combination sum

Given a set of candidate numbers (candidates) (without duplicates) and a target
number (target), find all unique combinations in candidates where the candidate
numbers sums to target.

The same repeated number may be chosen from candidates unlimited number of
times.

Note:

    All numbers (including target) will be positive integers.
    The solution set must not contain duplicate combinations.

Example 1:

Input: candidates = [2,3,6,7], target = 7,
A solution set is:
[
  [7],
  [2,2,3]
]

Example 2:

Input: candidates = [2,3,5], target = 8,
A solution set is:
[
  [2,2,2,2],
  [2,3,3],
  [3,5]
]
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

using std::cout;
using std::get;
using std::ostream;
using std::queue;
using std::sort;
using std::string;
using std::tuple;
using std::unordered_set;
using std::vector;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& container) {
  auto first = begin(container);
  auto last = end(container);
  --last;
  os << '{';
  while (first != last) {
    os << *first << ',';
    ++first;
  }

  os << *first << '}';

  return os;
}

class Solution {
	
  static void generate_hash_index(const vector<int>& seq, string& hash_index) {
    hash_index.clear();

    for (int n : seq) {
      while (n) {
        hash_index.push_back(n % 10 + '0');
        n /= 10;
      }

      hash_index.push_back(',');
    }

    hash_index.pop_back();
  }

 public:
  vector<vector<int>> combinationSum(vector<int>& candidates,
                                     const int target) {
    size_t candidates_size{candidates.size()};

    for (size_t i{}; i < candidates_size; i++) {
      const int n_times{target / candidates[i] - 1};
      if (n_times > 0)
        candidates.insert(end(candidates), n_times, candidates[i]);
    }

    sort(begin(candidates), end(candidates));

    candidates_size = candidates.size();

    queue<tuple<size_t, int, vector<int>>> q{{make_tuple(0, 0, vector<int>{})}};

    unordered_set<int> already_visited_first_numbers{};
    unordered_set<string> already_visited_sequences{};
    string hash_index{};
    hash_index.reserve(1024);

    vector<vector<int>> unique_combinations{};

    while (!q.empty()) {
      const size_t current_pos{get<0>(q.front())};
      const int current_sum{get<1>(q.front())};
      vector<int> current_seq{move(get<2>(q.front()))};
      q.pop();

      for (size_t i{current_pos}; i < candidates_size; i++) {
        if (target == current_sum + candidates[i]) {
          current_seq.emplace_back(candidates[i]);
          generate_hash_index(current_seq, hash_index);
          if (already_visited_sequences.count(hash_index))
            break;
          already_visited_sequences.insert(hash_index);
          unique_combinations.push_back(move(current_seq));
          break;

        } else if (current_sum + candidates[i] > target)
          break;

        else {
          if (current_seq.empty()) {
            if (already_visited_first_numbers.count(candidates[i]))
              continue;
            already_visited_first_numbers.insert(candidates[i]);
            q.emplace(
                make_tuple(i + 1, candidates[i], vector<int>{candidates[i]}));
          } else {
            current_seq.emplace_back(candidates[i]);
            generate_hash_index(current_seq, hash_index);
            if (already_visited_sequences.count(hash_index)) {
              current_seq.pop_back();
              continue;
            }
            already_visited_sequences.insert(hash_index);
            if (i < candidates_size - 1) {
              q.emplace(
                  make_tuple(i + 1, current_sum + candidates[i], current_seq));
              current_seq.pop_back();
            } else {
              q.emplace(make_tuple(i + 1, current_sum + candidates[i],
                                   move(current_seq)));
              break;
            }
          }
        }
      }
    }

    return unique_combinations;
  }
};

int main() {
  Solution s{};
  vector<int> input{2, 3, 6, 7};
  vector<vector<int>> result_set{s.combinationSum(input, 7)};

  cout << '\n';
  for (const vector<int>& v : result_set)
    cout << v << '\n';

  input.assign({2, 3, 5});
  result_set = s.combinationSum(input, 8);

  cout << '\n';
  for (const vector<int>& v : result_set)
    cout << v << '\n';

  input.assign({92,  71,  89, 74,  102, 91,  70,  119, 86, 116,
                114, 106, 80, 81,  115, 99,  117, 93,  76, 77,
                111, 110, 75, 104, 95,  112, 94,  73});
  result_set = s.combinationSum(input, 310);

  cout << '\n';
  for (const vector<int>& v : result_set)
    cout << v << '\n';

  return 0;
}
