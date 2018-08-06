/*
102. Binary tree level order traversal

Given a binary tree, return the level order traversal of its nodes' values. (ie,
from left to right, level by level).

For example:
Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7

return its level order traversal as:

[
  [3],
  [9,20],
  [15,7]
]
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& data) {
  if (data.empty()) {
    os << "data is empty";
    return os;
  }
  os << "  [";
  for (size_t i{}; i < data.size() - 1; i++)
    os << data[i] << ',';
  os << data.back() << ']';
  return os;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& data) {
  if (data.empty()) {
    os << "data is empty";
    return os;
  }

  os << "\n[\n";
  for (const auto& row : data)
    os << row << '\n';
  os << "]\n";

  return os;
}

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(const int x) : val{x}, left{}, right{} {}
};

class Solution {
 public:
  vector<vector<int>> levelOrder(const TreeNode* root) {
    vector<vector<int>> result{};
    if (!root)
      return result;
    queue<const TreeNode*> qt{{root}};
    queue<const TreeNode*> ql{};

    do {
      vector<int> level_nodes{};
      while (!qt.empty()) {
        const TreeNode* tn{qt.front()};
        qt.pop();
        level_nodes.emplace_back(tn->val);
        if (tn->left)
          ql.emplace(tn->left);
        if (tn->right)
          ql.emplace(tn->right);
      }
      qt.swap(ql);
      result.emplace_back(move(level_nodes));
    } while (!qt.empty());

    return result;
  }
};

int main() {
  Solution s{};

  TreeNode root1{3}, lc1{9}, rc1{20}, rc1_lc1{15}, rc1_rc1{7};
  root1.left = &lc1;
  root1.right = &rc1;
  rc1.left = &rc1_lc1;
  rc1.right = &rc1_rc1;

  const auto bt_level_order_traversal{s.levelOrder(&root1)};
  cout << "s.recoverTree([3, 9, 20, null, null, 15, 7]) -> "
       << bt_level_order_traversal << '\n';

  return 0;
}