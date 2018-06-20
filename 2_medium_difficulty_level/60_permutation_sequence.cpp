/*
60. leetcode coding challenge: Permutation Sequence

The set [1,2,3,...,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order, we get the following
sequence for n = 3:

    "123"
    "132"
    "213"
    "231"
    "312"
    "321"

Given n and k, return the kth permutation sequence.

Note:

    Given n will be between 1 and 9 inclusive.
    Given k will be between 1 and n! inclusive.

Example 1:

Input:  n = 3, k = 3
Output: "213"

Example 2:

Input:  n = 4, k = 9
Output: "2314"
*/

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>

using namespace std;

class Solution {
 public:
  string getPermutation(const int n, const int k) {
    string seq(n, '1');
    iota(begin(seq), end(seq), '1');

    if (1 == k)
      return seq;

    for (int i{2}; i <= k; i++)
      next_permutation(begin(seq), end(seq));

    return seq;
  }
};

int main() {
  Solution s{};

  cout << "s.getPermutation() -> " << s.getPermutation(3, 3)
       << '\n';  // expected output: "213"
  cout << "s.getPermutation() -> " << s.getPermutation(4, 9)
       << '\n';  // expected output: "2314"

  return 0;
}