/*
111. Leetcode coding challenge: Minimum depth of a binary tree

Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root
node down to the nearest leaf node.

Note: A leaf is a node with no children.

Example:

Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7

return its minimum depth = 2.
*/

#include <iostream>
#include <queue>
#include <string>
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
  int minDepth(TreeNode* root) {
    if (!root)
      return 0;
    if (!root->left && !root->right)
      return 1;

    queue<pair<const TreeNode*, size_t>> q{{make_pair(root, 1u)}};
    size_t mininum_depth{string::npos};

    while (!q.empty()) {
      const TreeNode* node{q.front().first};
      size_t depth{q.front().second};
      q.pop();

      if (!node->left && !node->right) {
        if (depth < mininum_depth)
          mininum_depth = depth;
        continue;
      }

      depth++;

      if (depth >= mininum_depth)
        continue;

      if (node->left)
        q.emplace(make_pair(node->left, depth));
      if (node->right)
        q.emplace(make_pair(node->right, depth));
    }

    return mininum_depth;
  }
};

int main() {
  Solution s{};

  TreeNode tr1{3}, lch_1{9}, rch_1{20};
  tr1.left = &lch_1;
  tr1.right = &rch_1;
  TreeNode rch_lch_1{15}, rch_rch_1{7};
  rch_1.left = &rch_lch_1;
  rch_1.right = &rch_rch_1;

  cout << "s.minDepth({3,9,20,null,null,15,7}) -> " << s.minDepth(&tr1) << '\n';

  return 0;
}