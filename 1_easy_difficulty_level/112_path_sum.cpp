/*
112. Leetcode coding challenge: Path sum

Given a binary tree and a sum, determine if the tree has a root-to-leaf path
such that adding up all the values along the path equals the given sum.

Note: A leaf is a node with no children.

Example:

Given the below binary tree and sum = 22,

      5
     / \
    4   8
   /   / \
  11  13  4
 /  \      \
7    2      1

return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
*/

#include <iomanip>
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
  bool hasPathSum(const TreeNode* root, const int sum) {
    if (!root)
      return false;
    if (sum == root->val && !root->left && !root->right)
      return true;

    queue<pair<const TreeNode*, int>> q{{make_pair(root, root->val)}};

    while (!q.empty()) {
      const TreeNode* node{q.front().first};
      const int path_sum{q.front().second};
      q.pop();

      if (!node->left && !node->right) {
        if (path_sum == sum)
          return true;
        continue;
      }

      if (node->left)
        q.emplace(make_pair(node->left, path_sum + node->left->val));
      if (node->right)
        q.emplace(make_pair(node->right, path_sum + node->right->val));
    }

    return false;
  }
};

int main() {
  Solution s{};

  TreeNode tr1{5}, lch_1{4}, rch_1{8};
  tr1.left = &lch_1;
  tr1.right = &rch_1;
  TreeNode lch_lch_1{11}, lch_lch_lch_1{7}, lch_lch_rch_1{2};
  lch_1.left = &lch_lch_1;
  lch_lch_1.left = &lch_lch_lch_1;
  lch_lch_1.right = &lch_lch_rch_1;
  TreeNode rch_lch_1{13}, rch_rch_1{4}, rch_rch_rch_1{1};
  rch_1.left = &rch_lch_1;
  rch_1.right = &rch_rch_1;
  rch_rch_1.right = &rch_rch_rch_1;

  cout << boolalpha << "s.hasPathSum({5,4,8,11,null,13,4,7,2,null,1}, 22) -> "
       << s.hasPathSum(&tr1, 22) << noboolalpha << '\n';

  return 0;
}
