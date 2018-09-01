/*
377. Combination sum IV (difficulty level: medium)

Given an integer array with all positive numbers and no duplicates, find the
number of possible combinations that add up to a positive integer target.

Example:

nums = [1,1,1,1,2,2,3]
target = 4

The possible combination ways are:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)

Note that different sequences are counted as different combinations.

Therefore the output is 7.

Follow up:
What if negative numbers are allowed in the given array?
How does it change the problem?
What limitation we need to add to the question to allow negative numbers?
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

using namespace std;

template <typename T>
void print_range(T&& first, T&& last) {
  if (first == last)
    return;
  --last;
  cout << '[';
  for_each(forward<T>(first), forward<T>(last),
           [](const auto& data) { cout << data << ','; });
  cout << *last << "]\n";
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
  int combinationSum4(vector<int>& nums, const int target) {
    multiset<int> sorted_nums{cbegin(nums), cend(nums)};
    auto start = cbegin(sorted_nums);

    while (start != end(sorted_nums)) {
      const int current_num{*start};
      const int cnt{target / current_num};
      const int number_freq = sorted_nums.count(current_num);
      if (cnt > number_freq) {
        for (int i{}; i < cnt - number_freq; ++i)
          sorted_nums.insert(current_num);
      }

      start = sorted_nums.upper_bound(current_num);
    }

    const size_t nums_size{sorted_nums.size()};
    nums.reserve(nums_size);
    nums.assign(cbegin(sorted_nums), cend(sorted_nums));
    // print_range(cbegin(nums), cend(nums));

    unordered_set<string> already_visited_sequences{};
    unordered_set<int> already_visited_first_elements{};
    string hash_index{};
    hash_index.reserve(1024);

    int unique_combinations_count{};

    size_t i{};

    while (i < nums_size) {
      if (already_visited_first_elements.find(nums[i]) !=
          end(already_visited_first_elements)) {
        i = static_cast<size_t>(
            upper_bound(cbegin(nums) + i + 1, cend(nums), nums[i]) -
            cbegin(nums));
        continue;
      }
      already_visited_first_elements.insert(nums[i]);
      if (target == nums[i]) {
        unique_combinations_count++;
        i = static_cast<size_t>(
            upper_bound(cbegin(nums) + i + 1, cend(nums), nums[i]) -
            cbegin(nums));
        continue;
      }
      queue<tuple<int, vector<int>, unordered_set<size_t>>> q{{make_tuple(
          nums[i], vector<int>{nums[i]}, unordered_set<size_t>{i})}};

      while (!q.empty()) {
        const int current_sum{get<0>(q.front())};
        vector<int> current_seq{move(get<1>(q.front()))};
        unordered_set<size_t> visited_indices{move(get<2>(q.front()))};
        q.pop();

        size_t j{};
        while (j < nums_size) {
          if (visited_indices.find(j) != end(visited_indices)) {
            j++;
            continue;
          }
          visited_indices.insert(j);
          if (target == current_sum + nums[j]) {
            unique_combinations_count++;
            break;

          } else if (current_sum + nums[j] > target)
            break;

          else {
            current_seq.emplace_back(nums[j]);
            generate_hash_index(current_seq, hash_index);
            if (already_visited_sequences.find(hash_index) !=
                end(already_visited_sequences)) {
              current_seq.pop_back();
              j = static_cast<size_t>(
                  upper_bound(cbegin(nums) + j + 1, cend(nums), nums[j]) -
                  cbegin(nums));
              continue;
            }
            already_visited_sequences.insert(hash_index);
            if (j < nums_size - 1) {
              q.emplace(make_tuple(current_sum + nums[j], current_seq,
                                   visited_indices));
              current_seq.pop_back();
            } else if (nums_size - 1 == j) {
              q.emplace(make_tuple(current_sum + nums[j], move(current_seq),
                                   move(visited_indices)));
              break;
            }
          }

          visited_indices.erase(j);
          j++;
        }
      }
      i++;
    }

    return unique_combinations_count;
  }
};

int main() {
  Solution s{};
  vector<int> input{1, 2, 3};
  cout << "s.combinationSum4([1, 2, 3], 4) -> " << s.combinationSum4(input, 4)
       << '\n';

  return 0;
}
