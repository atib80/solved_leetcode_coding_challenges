/*
575. Distribute candies (difficulty level: easy)

Given an integer array with even length, where different numbers in this array
represent different kinds of candies. Each number means one candy of the
corresponding kind. You need to distribute these candies equally in number to
brother and sister. Return the maximum number of kinds of candies the sister
could gain.

Example 1:

Input: candies = [1,1,2,2,3,3]
Output: 3
Explanation:
There are three different kinds of candies (1, 2 and 3), and two candies for
each kind. Optimal distribution: The sister has candies [1,2,3] and the brother
has candies [1,2,3], too. The sister has three different kinds of candies.

Example 2:

Input: candies = [1,1,2,3]
Output: 2
Explanation: For example, the sister has candies [2,3] and the brother has
candies [1,1]. The sister has two different kinds of candies, the brother has
only one kind of candies.

Note:

    The length of the given array is in range [2, 10,000], and will be even.
    The number in given array is in range [-100,000, 100,000].
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  static int candy_kinds[200001];
  static vector<int> indices;

 public:
  Solution() { indices.reserve(10000); }

  int distributeCandies(const vector<int>& candies) const {
    const size_t half_of_candies{candies.size() / 2};
    size_t unique_candies{};
    indices.clear();

    for (const int c : candies) {
      const int index{100000 + c};
      if (!candy_kinds[index]) {
        candy_kinds[index] = 1;
        indices.emplace_back(index);
        unique_candies++;
      }
    }

    for (const int i : indices)
      candy_kinds[i] = 0;

    return min(half_of_candies, unique_candies);
  }
};

int Solution::candy_kinds[200001]{};
vector<int> Solution::indices{};

int main() {
  Solution s{};

  vector<int> candies{1, 1, 2, 2, 3, 3};

  cout << "s.distributeCandies([1,1,2,2,3,3]) -> "
       << s.distributeCandies(candies) << '\n';  // expected output: 3
  candies.assign({1, 1, 2, 3});
  cout << "s.distributeCandies([1,1,2,3]) -> " << s.distributeCandies(candies)
       << '\n';  // expected output: 2

  return 0;
}
