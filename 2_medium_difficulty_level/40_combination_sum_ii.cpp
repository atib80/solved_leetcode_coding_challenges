/*
Given a collection of candidate numbers (candidates) and a target number
(target), find all unique combinations in candidates where the candidate numbers
sums to target.

Each number in candidates may only be used once in the combination.

Note:

    All numbers (including target) will be positive integers.
    The solution set must not contain duplicate combinations.

Example 1:

Input: candidates = [10,1,2,7,6,1,5], target = 8,
A solution set is:
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]

Example 2:

Input: candidates = [2,5,2,1,2], target = 5,
A solution set is:
[
  [1,2,2],
  [5]
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
using std::for_each;
using std::get;
using std::queue;
using std::sort;
using std::string;
using std::tuple;
using std::unordered_set;
using std::vector;

template <typename T>
void print_range(T&& first, T&& last) {
  if (first == last)
    return;
  --last;
  for_each(first, last, [](const auto& data) { cout << data << ','; });

  cout << *last << '\n';
}

inline void generate_hash_index(const vector<int>& seq, string& hash_index) {
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

class Solution {
 public:
  vector<vector<int>> combinationSum2(vector<int>& candidates,
                                      const int target) {
    const size_t candidates_size{candidates.size()};

    sort(begin(candidates), end(candidates));

    queue<tuple<size_t, int, vector<int>>> q{{make_tuple(0, 0, vector<int>{})}};

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
          unique_combinations.push_back(move(current_seq));
          break;

        } else if (current_sum + candidates[i] > target)
          break;

        else {
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
          } else if (candidates_size - 1 == i) {
            q.emplace(make_tuple(i + 1, current_sum + candidates[i],
                                 move(current_seq)));
            break;
          }
        }
      }
    }

    return unique_combinations;
  }
};

int main() {
  Solution s{};
  vector<int> input{10, 1, 2, 7, 6, 1, 5};
  vector<vector<int>> result_set{s.combinationSum2(input, 8)};

  cout << '\n';
  for (const vector<int>& v : result_set)
    print_range(begin(v), end(v));

  input.assign({2, 5, 2, 1, 2});
  result_set = s.combinationSum2(input, 5);

  cout << '\n';
  for (const vector<int>& v : result_set)
    print_range(begin(v), end(v));

  /*
  input.assign({92,  71,  89, 74,  102, 91,  70,  119, 86, 116,
                114, 106, 80, 81,  115, 99,  117, 93,  76, 77,
                111, 110, 75, 104, 95,  112, 94,  73});
  result_set = s.combinationSum2(input, 310);

  cout << '\n';
  for (const vector<int>& v : result_set)
    print_range(begin(v), end(v));
  */

  return 0;
}
