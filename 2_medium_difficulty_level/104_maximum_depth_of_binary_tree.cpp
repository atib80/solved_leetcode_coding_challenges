/*
Leetcode coding challenge: Maximum Depth of Binary Tree

Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root
node down to the farthest leaf node.

Note: A leaf is a node with no children.

Example:

Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7

return its depth = 3.
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
  TreeNode(const int x) : val(x), left{}, right{} {}
};

class Solution {
 public:
  int maxDepth(TreeNode* root) {
    if (!root)
      return 0;

    size_t max_depth{1};
    queue<pair<TreeNode*, size_t>> q{{make_pair(root, 1)}};

    while (!q.empty()) {
      TreeNode* n{q.front().first};
      const size_t current_depth{q.front().second};
      q.pop();

      if (!n)
        continue;

      if (current_depth > max_depth)
        max_depth = current_depth;

      if (n->left)
        q.emplace(make_pair(n->left, current_depth + 1));
      if (n->right)
        q.emplace(make_pair(n->right, current_depth + 1));
    }

    return max_depth;
  }
};

int main() {
  Solution s{};

  TreeNode root{3};
  TreeNode left{9};
  TreeNode right{20};
  TreeNode right_left{15};
  TreeNode right_right{7};
  root.left = &left;
  root.right = &right;
  right.left = &right_left;
  right.right = &right_right;

  cout << "s.maxDepth(root) = " << s.maxDepth(&root) << '\n';

  return 0;
}
