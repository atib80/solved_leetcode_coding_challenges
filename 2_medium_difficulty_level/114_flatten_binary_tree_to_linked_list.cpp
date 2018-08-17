/*
114. Leetcode coding challenge: Flatten binary tree to linked list

Given a binary tree, flatten it to a linked list in-place.

For example, given the following tree:

    1
   / \
  2   5
 / \   \
3   4   6

The flattened tree should look like:

1
 \
  2
   \
    3
     \
      4
       \
        5
         \
          6

*/

#include <iostream>
#include <queue>
#include <stack>

using std::cout;
using std::queue;
using std::stack;

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(const int x) : val{x}, left{}, right{} {}
};

class Solution {
  TreeNode* right_start{};

 public:
  Solution() = default;

  void flatten(TreeNode* root) {
    if (!root || (!root->left && !root->right))
      return;

    right_start = root;

    queue<TreeNode*> q{{root->left}};
    stack<TreeNode*> s{{root->right}};

    while (!q.empty()) {
      TreeNode* current_node{q.front()};
      q.pop();

      if (!current_node) {
        if (!s.empty()) {
          q.emplace(s.top());
          s.pop();
        }
        continue;
      }

      q.emplace(current_node->left);
      s.emplace(current_node->right);
      right_start->right = current_node;
      right_start->left = nullptr;
      right_start = right_start->right;
    }
  }
};

int main() {
  Solution s{};

  TreeNode root1{1}, lc1{2}, rc1{5}, rc1_rc1{6}, lc1_lc1{3}, lc1_rc1{4};
  root1.left = &lc1;
  root1.right = &rc1;
  lc1.left = &lc1_lc1;
  lc1.right = &lc1_rc1;
  rc1.right = &rc1_rc1;

  s.flatten(&root1);
  const TreeNode* bt_node{&root1};
  cout << '[';
  while (bt_node) {
    cout << bt_node->val << " -> ";
    if (bt_node->left)
      cout << "bt_node->left is not nullptr!\n";
    bt_node = bt_node->right;
  }
  cout << "nullptr]";

  return 0;
}
