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
  vector<int> numbers;
  vector<int> current_seq;
  unordered_set<size_t> visited_indices;
  unordered_set<string> already_visited_sequences;
  string hash_index;
  size_t numbers_size;
  int target_sum;

  void generate_hash_index() {
    hash_index.clear();

    for (int n : current_seq) {
      while (n) {
        hash_index.push_back(n % 10 + '0');
        n /= 10;
      }

      hash_index.push_back(',');
    }

    hash_index.pop_back();
  }

  void find_count_of_unique_combinations_for_given_target_sum(
      int& unique_combinations_count,
      const int current_sum) {
    size_t j{};
    while (j < numbers_size) {
      if (visited_indices.find(j) != end(visited_indices)) {
        j++;
        continue;
      }
      visited_indices.insert(j);
      if (target_sum == current_sum + numbers[j]) {
        unique_combinations_count++;
        visited_indices.erase(j);
        return;

      } else if (current_sum + numbers[j] > target_sum) {
        visited_indices.erase(j);
        return;
      }

      else {
        current_seq.emplace_back(numbers[j]);
        generate_hash_index();
        if (already_visited_sequences.find(hash_index) !=
            end(already_visited_sequences)) {
          current_seq.pop_back();
          visited_indices.erase(j);
          j = static_cast<size_t>(
              upper_bound(cbegin(numbers) + j + 1, cend(numbers), numbers[j]) -
              cbegin(numbers));
          continue;
        }
        already_visited_sequences.insert(hash_index);
        if (j < numbers_size)
          find_count_of_unique_combinations_for_given_target_sum(
              unique_combinations_count, current_sum + numbers[j]);
        current_seq.pop_back();
      }

      visited_indices.erase(j);
      j++;
    }
  }

 public:
  Solution() { hash_index.reserve(1024); }
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

    numbers_size = sorted_nums.size();
    numbers.reserve(numbers_size);
    numbers.assign(cbegin(sorted_nums), cend(sorted_nums));
    target_sum = target;
    // print_range(cbegin(numbers), cend(numbers));

    current_seq.reserve(numbers_size);

    already_visited_sequences.clear();

    unordered_set<int> already_visited_first_elements{};
    int unique_combinations_count{};

    size_t i{};

    while (i < numbers_size) {
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

      visited_indices.clear();
      visited_indices.insert(i);
      current_seq.clear();
      current_seq.emplace_back(nums[i]);

      find_count_of_unique_combinations_for_given_target_sum(
          unique_combinations_count, nums[i]);
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
