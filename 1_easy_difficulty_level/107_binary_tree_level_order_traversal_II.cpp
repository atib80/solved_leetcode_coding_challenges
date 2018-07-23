/*
Given a binary tree, return the bottom-up level order traversal of its nodes'
values. (ie, from left to right, level by level from leaf to root).

For example:
Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7

return its bottom-up level order traversal as:

[
  [15,7],
  [9,20],
  [3]
]
*/
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& data) {
  if (data.empty()) {
    os << "data is empty\n";
    return os;
  }
  os << "\n  [";
  for (size_t i{}; i < data.size() - 1; i++)
    os << data[i] << ',';
  os << data.back() << "]";
  return os;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& data) {
  if (data.empty()) {
    os << "data is empty\n";
    return os;
  }

  os << "\n[\n";
  for (const auto& row : data)
    os << row;
  os << "\n]\n";

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
  vector<vector<int>> levelOrderBottom(const TreeNode* root) {
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

    if (result.size() > 1)
      reverse(begin(result), end(result));
    return result;
  }
};

int main() {
  Solution s{};

  TreeNode tr1{3}, lt_lch_1{9}, lt_rch_1{20};
  tr1.left = &lt_lch_1;
  tr1.right = &lt_rch_1;
  TreeNode lt_rch_lch_1{15}, lt_rch_rch_1{7};
  lt_rch_1.left = &lt_rch_lch_1;
  lt_rch_1.right = &lt_rch_rch_1;

  const vector<vector<int>> output{s.levelOrderBottom(&tr1)};

  cout << "s.levelOrderBottom({3,9,20,null,null,15,7}) -> " << output << '\n';

  return 0;
}