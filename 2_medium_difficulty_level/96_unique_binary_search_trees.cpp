/*
Given n, how many structurally unique BST's (binary search trees) that store
values 1 ... n?

Example:

Input: 3
Output: 5
Explanation:
Given n = 3, there are a total of 5 unique BST's:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
*/

#include <iostream>
#include <vector>

using namespace std;

// Definition for a binary tree node.
// struct TreeNode {
//   int val;
//   TreeNode* left;
//   TreeNode* right;
//   TreeNode(const int x) : val{x}, left{}, right{} {}
//   ~TreeNode() {
//     if (left) {
//       delete left;
//       left = nullptr;
//     }
//     if (right) {
//       delete right;
//       right = nullptr;
//     }
//   }
// };

class Solution {
 public:
  int numTrees(const size_t n) {
    if (!n)
      return 0;
    if (1 == n)
      return 1;

    vector<int> dp(n + 1, 0);
    dp[0] = dp[1] = 1;
    for (size_t i{2}; i <= n; i++)
      for (size_t j{}; j < i; j++)
        dp[i] += dp[j] * dp[i - j - 1];

    return dp[n];
  }
};

int main() {
  Solution s{};

  cout << "s.numTrees(0) -> " << s.numTrees(0) << '\n';
  cout << "s.numTrees(1) -> " << s.numTrees(1) << '\n';
  cout << "s.numTrees(2) -> " << s.numTrees(2) << '\n';
  cout << "s.numTrees(3) -> " << s.numTrees(3) << '\n';
  cout << "s.numTrees(4) -> " << s.numTrees(4) << '\n';
  cout << "s.numTrees(5) -> " << s.numTrees(5) << '\n';

  return 0;
}
