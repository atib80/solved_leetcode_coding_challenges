/*
129. Leetcode coding challenge: Sum root to leaf numbers (difficulty level:
medium)

Given a binary tree containing digits from 0-9 only, each root-to-leaf path
could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

Note: A leaf is a node with no children.

Example:

Input: [1,2,3]
    1
   / \
  2   3
Output: 25
Explanation:
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.
Therefore, sum = 12 + 13 = 25.

Example 2:

Input: [4,9,0,5,1]
    4
   / \
  9   0
 / \
5   1
Output: 1026
Explanation:
The root-to-leaf path 4->9->5 represents the number 495.
The root-to-leaf path 4->9->1 represents the number 491.
The root-to-leaf path 4->0 represents the number 40.
Therefore, sum = 495 + 491 + 40 = 1026.
*/

#include <iostream>
#include <queue>
#include <utility>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(const int x) : val{x}, left{}, right{} {}
};

class Solution {
 public:
  int sumNumbers(const TreeNode* root) const {
    if (!root)
      return 0;

    queue<pair<const TreeNode*, int>> q{{make_pair(root, root->val)}};

    int total_sum{};

    while (!q.empty()) {
      const TreeNode* node{q.front().first};
      const int path_sum{q.front().second};
      q.pop();

      if (!node->left && !node->right)
        total_sum += path_sum;

      else {
        if (node->left)
          q.emplace(make_pair(node->left, path_sum * 10 + node->left->val));
        if (node->right)
          q.emplace(make_pair(node->right, path_sum * 10 + node->right->val));
      }
    }

    return total_sum;
  }
};

int main() {
  Solution s{};

  TreeNode root1{1}, lc1{2}, rc1{3};
  root1.left = &lc1;
  root1.right = &rc1;
  cout << "s.sumNumbers([1,2,3]) -> " << s.sumNumbers(&root1)
       << '\n';  // expected output: 25

  TreeNode root2{4}, lc2{9}, rc2{0}, lc2_lc2{5}, lc2_rc2{1};
  root2.left = &lc2;
  root2.right = &rc2;
  lc2.left = &lc2_lc2;
  lc2.right = &lc2_rc2;
  cout << "s.sumNumbers([4,9,0,5,1]) -> " << s.sumNumbers(&root2)
       << '\n';  // expected output: 1026

  return 0;
}
