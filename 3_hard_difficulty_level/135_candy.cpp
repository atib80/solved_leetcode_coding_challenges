/*
135. Leetcode coding challenge: Candy

There are N children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following
requirements:

    Each child must have at least one candy.
    Children with a higher rating get more candies than their neighbors.

What is the minimum candies you must give?

Example 1:

Input: [1,0,2]
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

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int candy(const vector<int>& ratings) {
    const size_t ratings_count{ratings.size()};

    if (!ratings_count)
      return 0;
    if (1 == ratings_count)
      return 1;

    size_t candies{ratings_count}, last_neighbor_candy_count{},
        last_neighbor_index{};

    for (size_t i{}; i < ratings_count; i++) {
      bool is_peak_rating{};
      if (!i)
        is_peak_rating = ratings[i] > ratings[i + 1];
      else if (ratings_count - 1 == i)
        is_peak_rating = ratings[i] > ratings[i - 1];
      else
        is_peak_rating =
            ratings[i] > ratings[i - 1] || ratings[i] > ratings[i + 1];

      if (is_peak_rating) {
        if (i - last_neighbor_index == 1) {
          last_neighbor_candy_count++;
          candies += last_neighbor_candy_count;
        } else {
          candies++;
          last_neighbor_candy_count = 1;
        }

        last_neighbor_index = i;
      }
    }

    return candies;
  }
};

int main() {
  Solution s{};

  cout << "s.candy([1,0,2]) -> " << s.candy({1, 0, 2})
       << '\n';  // expected output: 5
  cout << "s.candy([1,2,1]) -> " << s.candy({1, 2, 1})
       << '\n';  // expected output: 4
  cout << "s.candy([1,2,3]) -> " << s.candy({1, 2, 3})
       << '\n';  // expected output: 5

  return 0;
}
