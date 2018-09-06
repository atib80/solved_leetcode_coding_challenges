/*
377. Combination sum IV (difficulty level: medium)

(iterative solution implemented by using a simple method for shifting indices)

Given an integer array with all positive numbers and no duplicates, find the
number of possible combinations that add up to a positive integer target.

Example:

nums = [1,2,3]
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
#include <set>
#include <string>
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
  static void generate_hash_index(const multiset<int>& seq,
                                  string& hash_index) {
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

  static uint64_t factorial(const size_t n) {
    if (n < 2)
      return 1;
    uint64_t fact{n};
    for (size_t i{n - 1}; i > 1; i--)
      fact *= i;
    return fact;
  }

  static uint64_t calculate_count_of_unique_permutations_for_given_sequence(
      const multiset<int>& seq) {
    vector<size_t> div_factors{};
    auto start{cbegin(seq)};
    const auto last{cend(seq)};

    while (start != last) {
      const int num{*start};
      const size_t num_freq{seq.count(num)};
      if (num_freq > 1)
        div_factors.emplace_back(num_freq);
      start = seq.upper_bound(num);
    }

    if (div_factors.empty())
      return factorial(seq.size());

    if (1 == div_factors.size() && seq.size() == div_factors[0])
      return 1;

    const auto max_element_iter_pos{
        max_element(begin(div_factors), end(div_factors))};

    const uint64_t max_factor{*max_element_iter_pos};
    div_factors.erase(max_element_iter_pos);
    uint64_t result{seq.size()}, div_factor{1};

    for (uint64_t i{result - 1}; i > max_factor; i--)
      result *= i;

    for (const size_t d : div_factors)
      div_factor *= factorial(d);

    return result / div_factor;
  }

  static bool shift_indices(vector<size_t>& indices,
                            const size_t k,
                            const size_t nums_size) {
    bool carry{};

    for (int i = k - 1, offset{}; i >= 0; i--, offset++) {
      if (!i && indices[i] >= nums_size - k)
        return false;

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

    return true;
  }

 public:
  uint64_t combinationSum4(vector<int>& nums, const int target) const {
    multiset<int> sorted_nums{cbegin(nums), cend(nums)};
    auto start = cbegin(sorted_nums);
    bool number_last_digit_3_target_last_digit_0{0 == target % 10};

    uint64_t unique_combinations_count{};

    while (start != end(sorted_nums)) {
      const int current_num{*start};
      if (current_num >= target) {
        if (target == current_num)
          unique_combinations_count++;
        sorted_nums.erase(current_num);
      } else {
        if (number_last_digit_3_target_last_digit_0 && 3 != current_num % 10)
          number_last_digit_3_target_last_digit_0 = false;
        const int cnt{target / current_num};
        const int number_freq = sorted_nums.count(current_num);
        if (cnt > number_freq) {
          for (int i{}; i < cnt - number_freq; i++)
            sorted_nums.insert(current_num);
        }
      }

      start = sorted_nums.upper_bound(current_num);
    }

    if (number_last_digit_3_target_last_digit_0)
      return 0;

    const size_t nums_size{sorted_nums.size()};
    nums.reserve(nums_size);
    nums.assign(cbegin(sorted_nums), cend(sorted_nums));
    // print_range(begin(nums), end(nums));

    string hash_index{};
    hash_index.reserve(1024);
    unordered_set<string> already_visited_sequences{};

    for (size_t k{2}; k <= nums_size; k++) {
      int current_sum{};
      multiset<int> current_seq{};

      for (size_t i{nums_size - k}; i < nums_size; i++) {
        current_sum += nums[i];
        current_seq.insert(nums[i]);
      }
      if (current_sum < target)
        continue;
      if (target == current_sum) {
        unique_combinations_count +=
            calculate_count_of_unique_permutations_for_given_sequence(
                current_seq);
        continue;
      }

      vector<size_t> indices(k);
      for (size_t i{}; i < k; i++)
        indices[i] = i;
      already_visited_sequences.clear();
      bool is_process_next_k{};

      while (!is_process_next_k) {
        current_seq.clear();
        current_sum = 0;

        for (size_t i{}; i < k; i++) {
          current_seq.insert(nums[indices[i]]);
          current_sum += nums[indices[i]];
        }

        generate_hash_index(current_seq, hash_index);
        while (already_visited_sequences.find(hash_index) !=
               end(already_visited_sequences)) {
          indices[k - 1] = static_cast<size_t>(
              upper_bound(cbegin(nums) + indices[k - 1] + 1, cend(nums),
                          nums[indices[k - 1]]) -
              cbegin(nums));
          if (nums_size == indices[k - 1]) {
            indices[k - 1] = nums_size - 1;
            if (!shift_indices(indices, k, nums_size)) {
              is_process_next_k = true;
              break;
            }
            current_seq.clear();
            current_sum = 0;
            for (const size_t i : indices) {
              current_seq.insert(nums[i]);
              current_sum += nums[i];
            }

            if (current_sum > target) {
              is_process_next_k = true;
              break;
            }
          } else {
            const auto last_item{--end(current_seq)};
            current_sum -= *last_item;
            current_seq.erase(last_item);
            current_seq.insert(nums[indices[k - 1]]);
            current_sum += nums[indices[k - 1]];
          }

          generate_hash_index(current_seq, hash_index);
        }

        if (is_process_next_k)
          break;

        already_visited_sequences.insert(hash_index);

        if (target == current_sum) {
          unique_combinations_count +=
              calculate_count_of_unique_permutations_for_given_sequence(
                  current_seq);
          if (k - 1 == indices[k - 1])
            break;
          indices[k - 1] = nums_size - 1;
        } else if (current_sum > target) {
          if (k - 1 == indices[k - 1])
            break;
          indices[k - 1] = nums_size - 1;
        }

        if (!shift_indices(indices, k, nums_size))
          break;
      }
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
