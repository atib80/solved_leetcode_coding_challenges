/*
135. Leetcode coding challenge: Candy (difficulty level: hard)

There are N children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following
requirements:

    1. Each child must have at least one candy.
    2. Children with a higher rating get more candies than their neighbors.

What is the minimum candies you must give?

Example 1:

Input: [1,0,3,2]
Output: 5
Explanation: You can allocate to the first, second and third child with 2, 1, 2
candies respectively.

Example 2:

Input: [1,2,1]
Output: 4
Explanation: You can allocate to the first, second and third child with 1, 2, 1
candies respectively. The third child gets 1 candy because it satisfies the
above two conditions.

Example 3:

Input: [1,2,3]
Output: 6
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class Solution {
 public:
  int candy(const vector<int>& ratings) const {
    const size_t ratings_count{ratings.size()};

    if (!ratings_count)
      return 0;
    if (1 == ratings_count)
      return 1;

    size_t start_index{1}, prev_index{};
    vector<pair<size_t, size_t>> start_end_indices_of_slopes{};
    size_t candies_count{ratings_count};
    vector<size_t> peak_candy_counts(ratings_count, string::npos);

    while (start_index < ratings_count) {
      while (ratings[start_index] == ratings[prev_index]) {
        prev_index = start_index;
        start_index++;
      }

      const bool is_increasing_sequence{ratings[prev_index] <
                                        ratings[start_index]};
      size_t end_index{ratings_count};

      size_t i{start_index};

      for (; i < ratings_count; i++) {
        if ((is_increasing_sequence && !(ratings[i] > ratings[i - 1])) ||
            (!is_increasing_sequence && !(ratings[i] < ratings[i - 1]))) {
          end_index = i;
          start_end_indices_of_slopes.emplace_back(prev_index, i);
          break;
        }
      }

      if (i == ratings_count) {
        start_end_indices_of_slopes.emplace_back(prev_index, ratings_count);
        break;
      }

      start_index = end_index;
      prev_index = end_index - 1;
    }

    sort(begin(start_end_indices_of_slopes), end(start_end_indices_of_slopes),
         [](const pair<size_t, size_t>& lp, const pair<size_t, size_t>& rp) {
           return lp.second - lp.first > rp.second - rp.first;
         });

    for (const pair<size_t, size_t>& slope : start_end_indices_of_slopes) {
      size_t width{slope.second - slope.first};

      if (ratings[slope.first] < ratings[slope.second - 1]) {
        if (peak_candy_counts[slope.second - 1] != string::npos) {
          width--;
          candies_count += ((width - 1) * width) / 2;
        } else {
          size_t add_candies{((width - 1) * width) / 2};
          candies_count += add_candies;
          peak_candy_counts[slope.second - 1] = add_candies;
        }
      } else {
        if (peak_candy_counts[slope.first] != string::npos) {
          width--;
          candies_count += ((width - 1) * width) / 2;
        } else {
          size_t add_candies{((width - 1) * width) / 2};
          candies_count += add_candies;
          peak_candy_counts[slope.first] = add_candies;
        }
      }
    }

    return candies_count;
  }
};

int main() {
  Solution s{};

  cout << "s.candy([1,0,2]) -> " << s.candy({1, 0, 2})
       << '\n';  // expected output: 5
  cout << "s.candy([1,2,1]) -> " << s.candy({1, 2, 1})
       << '\n';  // expected output: 4
  cout << "s.candy([1,2,3]) -> " << s.candy({1, 2, 3})
       << '\n';  // expected output: 6

  cout << "s.candy([29, 51, 87, 87, 72, 12]) -> "     // 1 + 2 + 1 + 2 = 12
       << s.candy({29, 51, 87, 87, 72, 12}) << '\n';  // expected output: 12

  return 0;
}
