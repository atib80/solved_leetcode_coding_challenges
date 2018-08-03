/*
94. Leetcode coding challenge: Binary tree inorder traversal

Given a binary tree, return the inorder traversal of its nodes' values.

Example:

Input: [1,3,2,7,4,5,8]
      1
    /   \
   3     2
  / \   / \
 7   4 5   8

Output: [7,3,4,1,5,2,8]

Follow up: Recursive solution is trivial, could you do it iteratively?
*/

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& data) {
  if (data.empty()) {
    os << "data is empty\n";
    return os;
  }
  os << '[';
  for (size_t i{}; i < data.size() - 1; i++)
    os << data[i] << ',';
  os << data.back() << ']';
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
  vector<int> inorderTraversal(const TreeNode* root) {
    vector<int> output{};

    if (!root)
      return output;

    stack<const TreeNode*> s{};

    while (root || !s.empty()) {
      while (root) {
        s.emplace(root);
        root = root->left;
      }

      root = s.top();
      s.pop();

      output.emplace_back(root->val);
      root = root->right;
    }

    return output;
  }
};

int main() {
  Solution s{};

  TreeNode tr1{1}, lt_lch_1{3}, lt_rch_1{2};
  tr1.left = &lt_lch_1;
  tr1.right = &lt_rch_1;
  TreeNode lt_lch_lch_1{7}, lt_lch_rch_1{4}, lt_rch_lch_1{5}, lt_rch_rch_1{8};
  lt_lch_1.left = &lt_lch_lch_1;
  lt_lch_1.right = &lt_lch_rch_1;
  lt_rch_1.left = &lt_rch_lch_1;
  lt_rch_1.right = &lt_rch_rch_1;

  const auto output{s.inorderTraversal(&tr1)};
  cout << "s.inorderTraversal({1,3,2,7,4,5,8}) -> " << output << '\n';

  return 0;
}
