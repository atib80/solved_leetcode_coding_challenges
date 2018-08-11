/*
Given a binary tree and a sum, find all root-to-leaf paths where each path's sum
equals the given sum.

Note: A leaf is a node with no children.

Example:

Given the below binary tree and sum = 22,

      5
     / \
    4   8
   /   / \
  11  13  4
 /  \    / \
7    2  5   1

Return:

[
   [5,4,11,2],
   [5,8,4,5]
]
*/

#include <iostream>
#include <queue>
#include <tuple>
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
  vector<vector<int>> pathSum(const TreeNode* root, const int sum) const {
    if (!root)
      return vector<vector<int>>{};

    vector<vector<int>> root_to_leaf_paths{};

    queue<tuple<const TreeNode*, int, vector<int>>> q{
        {make_tuple(root, root->val, vector<int>{root->val})}};

    while (!q.empty()) {
      const TreeNode* node{get<0>(q.front())};
      const int current_sum{get<1>(q.front())};
      vector<int> path_nodes{move(get<2>(q.front()))};
      q.pop();

      if (!node->left && !node->right) {
        if (sum == current_sum)
          root_to_leaf_paths.emplace_back(move(path_nodes));
        continue;
      }

      if (node->left) {
        path_nodes.emplace_back(node->left->val);
        q.emplace(
            make_tuple(node->left, current_sum + node->left->val, path_nodes));
        path_nodes.pop_back();
      }

      if (node->right) {
        path_nodes.emplace_back(node->right->val);
        q.emplace(make_tuple(node->right, current_sum + node->right->val,
                             move(path_nodes)));
      }
    }

    return root_to_leaf_paths;
  }
};

int main() {
  Solution s{};

  TreeNode root1{5}, lc1{4}, rc1{8}, lc1_lc1{11}, lc1_lc1_lc1{7},
      lc1_lc1_rc1{2}, rc1_lc1{13}, rc1_rc1{4}, rc1_rc1_lc1{5}, rc1_rc1_rc1{1};
  root1.left = &lc1;
  root1.right = &rc1;
  lc1.left = &lc1_lc1;
  lc1_lc1.left = &lc1_lc1_lc1;
  lc1_lc1.right = &lc1_lc1_rc1;
  rc1.left = &rc1_lc1;
  rc1.right = &rc1_rc1;
  rc1_rc1.left = &rc1_rc1_lc1;
  rc1_rc1.right = &rc1_rc1_rc1;

  const auto output{s.pathSum(&root1, 22)};

  cout << "s.pathSum([7, 11, 2, 4, 5, 13, 8, 5, 4, 1], 22) -> " << output
       << '\n';

  return 0;
}
