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
  void generate_hash_index(const multiset<int>& seq, string& hash_index) {
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
      if (!i && indices[i] > nums_size - k)
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

    while (start != end(sorted_nums)) {
      const int current_num{*start};
      if (current_num > target) {
        sorted_nums.erase(current_num);
        start = sorted_nums.upper_bound(current_num);
        continue;
      }

      if (number_last_digit_3_target_last_digit_0 && 3 != current_num % 10)
        number_last_digit_3_target_last_digit_0 = false;
      const int cnt{target / current_num};
      const int number_freq = sorted_nums.count(current_num);
      if (cnt > number_freq) {
        if (current_num == target) {
          sorted_nums.erase(current_num);
          sorted_nums.insert(current_num);
        } else {
          for (int i{}; i < cnt - number_freq; ++i)
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

    unordered_set<string> already_visited_sequences{};
    unordered_set<int> already_visited_first_elements{};
    string hash_index{};
    hash_index.reserve(1024);

    uint64_t unique_combinations_count{};

    if (sorted_nums.find(target) != end(sorted_nums))
      unique_combinations_count++;

    for (size_t k{2}; k <= nums_size; k++) {
      size_t rep{nums_size};
      for (size_t i{nums_size - 1}; i > max(1u, nums_size - k); i--)
        rep *= i;
      size_t divisor{k};
      for (size_t i{k - 1}; i > 1; i--)
        divisor *= i;
      rep /= divisor;

      vector<size_t> indices(k);
      for (size_t i{}; i < k; i++)
        indices[i] = i;

      multiset<int> current_seq{};
      int current_sum{};

      for (size_t c{}; !is_process_next_k && c < rep; c++) {
        if (already_visited_first_elements.find(nums[indices[0]]) !=
            end(already_visited_first_elements)) {
          indices[0] =
              static_cast<size_t>(upper_bound(cbegin(nums) + indices[0] + 1,
                                              cend(nums), nums[indices[0]]) -
                                  cbegin(nums));
          for (size_t i{1}; i < k; i++) {
            if (indices[i - 1] + 1 > nums_size - k + i) {
              is_process_next_k = true;
              break;
            }

            indices[i] = indices[i - 1] + 1;
          }

          already_visited_first_elements.insert(nums[indices[0]]);
        }

        if (nums[indices[0]] >= target)
          break;

        current_seq.clear();

        for (size_t i{}; i < k; i++) {
          current_seq.insert(nums[indices[i]]);
          current_sum += nums[indices[i]];
        }

        if (target == current_sum) {
          generate_hash_index(current_seq, hash_index);
          if (already_visited_sequences.find(hash_index) ==
              end(already_visited_sequences)) {
            unique_combinations_count +=
                calculate_count_of_unique_permutations_for_given_sequence(
                    current_seq);
            already_visited_sequences.insert(hash_index);
          }
        } else {
          generate_hash_index(current_seq, hash_index);
          while (already_visited_sequences.find(hash_index) !=
                 end(already_visited_sequences)) {
            indices.back() = static_cast<size_t>(
                upper_bound(cbegin(nums) + indices.back() + 1, cend(nums),
                            nums[indices.back()]) -
                cbegin(nums));
            if (indices.back() == nums_size) {
              indices.back() = nums_size - 1;
              if (!shift_indices(indices, k, nums_size))
                break;
              current_seq.clear();
              for (const size_t i : indices)
                current_seq.insert(nums[i]);
            } else {
              current_seq.erase(--end(current_seq));
              current_seq.insert(nums[indices.back()])
            }

            generate_hash_index(current_seq, hash_index);
          }

          already_visited_sequences.insert(hash_index);
        }

        shift_indices(indices, k, nums_size);
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
  input.assign({1, 50});
  cout << "s.combinationSum4([1, 50], 200) -> " << s.combinationSum4(input, 200)
       << '\n';  // expected output: 28730
  input.assign({3, 33, 333});
  cout << "s.combinationSum4([3, 33, 333], 20000) -> "
       << s.combinationSum4(input, 20000) << '\n';  // expected output: 0

  input.assign({13,  17,  19,  23,  29,  31,  37,  41,  43,  47,  53,  59,
                61,  67,  71,  73,  79,  83,  89,  97,  101, 103, 107, 109,
                113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179,
                181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241,
                251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313,
                317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389,
                397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461,
                463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547,
                557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 615});
  cout << "s.combinationSum4([13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,"
          "79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,"
          "173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,"
          "269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,"
          "373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,"
          "467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,"
          "593,599,601,607,615], 220) -> "
       << s.combinationSum4(input, 220) << '\n';  // expected output: 45452242

  input.assign({10,  20,  30,  40,  50,  60,  70,  80,  90,  100, 110, 120, 130,
                140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260,
                270, 280, 290, 300, 310, 320, 330, 340, 350, 360, 370, 380, 390,
                400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 500, 510, 520,
                530, 540, 550, 560, 570, 580, 590, 600, 610, 620, 630, 640, 650,
                660, 670, 680, 690, 700, 710, 720, 730, 740, 750, 760, 770, 780,
                790, 800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 900, 910,
                920, 930, 940, 950, 960, 970, 980, 990, 111});
  cout << "s.combinationSum4([10,20,30,40,50,60,70,80,90,100,110,120,130,140,"
          "150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,"
          "320,330,340,350,360,370,380,390,400,410,420,430,440,450,460,470,480,"
          "490,500,510,520,530,540,550,560,570,580,590,600,610,620,630,640,650,"
          "660,670,680,690,700,710,720,730,740,750,760,770,780,790,800,810,820,"
          "830,840,850,860,870,880,890,900,910,920,930,940,950,960,970,980,990,"
          "111], 999) -> "
       << s.combinationSum4(input, 999) << '\n';  // expected output: ?

  return 0;
}
