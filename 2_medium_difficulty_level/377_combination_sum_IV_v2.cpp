/*
377. Combination sum IV (difficulty level: medium)

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
  vector<int> numbers;
  multiset<int> current_seq;
  unordered_set<string> already_visited_sequences;
  string hash_index;
  size_t numbers_size{};
  int target_sum{};

  void generate_hash_index(const multiset<int>& seq) {
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

  void find_count_of_unique_combinations_for_given_target_sum(
      const size_t start_pos,
      uint64_t& unique_combinations_count,
      const int current_sum) {
    size_t j{start_pos};
    while (j < numbers_size) {
      if (target_sum == current_sum + numbers[j]) {
        const auto iter_pos{current_seq.insert(numbers[j])};
        unique_combinations_count +=
            calculate_count_of_unique_permutations_for_given_sequence(
                current_seq);
        current_seq.erase(iter_pos);
        return;
      }

      if (current_sum + numbers[j] > target_sum)
        return;

      const auto iter_pos{current_seq.insert(numbers[j])};
      generate_hash_index(current_seq);
      if (already_visited_sequences.find(hash_index) !=
          end(already_visited_sequences)) {
        current_seq.erase(iter_pos);
        j = static_cast<size_t>(
            upper_bound(cbegin(numbers) + j + 1, cend(numbers), numbers[j]) -
            cbegin(numbers));
        continue;
      }
      already_visited_sequences.insert(hash_index);
      if (j + 1 < numbers_size)
        find_count_of_unique_combinations_for_given_target_sum(
            j + 1, unique_combinations_count, current_sum + numbers[j]);
      current_seq.erase(iter_pos);

      j++;
    }
  }

 public:
  Solution() { hash_index.reserve(1024); }

  uint64_t combinationSum4(vector<int>& nums, const int target) {
    multiset<int> sorted_nums{cbegin(nums), cend(nums)};
    auto start = cbegin(sorted_nums);
    bool number_last_digit_3_target_last_digit_0{0 == target % 10};

    while (start != end(sorted_nums)) {
      const int current_num{*start};
      if (current_num > target)
        break;
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

    numbers_size = sorted_nums.size();
    numbers.reserve(numbers_size);
    numbers.assign(cbegin(sorted_nums), cend(sorted_nums));    
    target_sum = target;
    print_range(begin(numbers), end(numbers));
    
    already_visited_sequences.clear();
    unordered_set<int> already_visited_first_elements{};
    uint64_t unique_combinations_count{};

    size_t i{};

    while (i < numbers_size) {
      if (numbers[i] > target)
        break;

      if (already_visited_first_elements.find(numbers[i]) !=
          end(already_visited_first_elements)) {
        i = static_cast<size_t>(
            upper_bound(cbegin(numbers) + i + 1, cend(numbers), numbers[i]) -
            cbegin(numbers));
        continue;
      }
      already_visited_first_elements.insert(numbers[i]);
      if (target == numbers[i]) {
        unique_combinations_count++;
        i = static_cast<size_t>(
            upper_bound(cbegin(numbers) + i + 1, cend(numbers), numbers[i]) -
            cbegin(numbers));
        continue;
      }

      current_seq.clear();
      current_seq.insert(numbers[i]);

      find_count_of_unique_combinations_for_given_target_sum(
          i + 1, unique_combinations_count, numbers[i]);
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
