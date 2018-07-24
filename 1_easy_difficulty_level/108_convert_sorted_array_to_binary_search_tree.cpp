/*
108. Convert sorted array to binary search tree

Given an array where elements are sorted in ascending order, convert it to a
height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in
which the depth of the two subtrees of every node never differ by more than 1.

Example:

Given the sorted array: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following
height balanced BST:

      0
     / \
   -3   9
   /   /
 -10  5
*/

#include <algorithm>
#include <iostream>
#include <memory>
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
  virtual ~TreeNode() {
    if (left)
      delete left;
    if (right)
      delete right;
  }
};

class Solution {
  static void construct_height_balanced_bst(TreeNode* root, const int value) {
    queue<TreeNode*> q{{root}};

    while (!q.empty()) {
      TreeNode* node{q.front()};
      q.pop();

      if (value < node->val) {
        if (nullptr == node->left) {
          node->left = new TreeNode{value};
          break;
        }

        if (value < node->left->val)
          q.emplace(node->left);
        else
          q.emplace(node->right);
      } else {
        if (nullptr == node->right) {
          node->right = new TreeNode{value};
          break;
        }

        if (value < node->right->val)
          q.emplace(node->left);
        else
          q.emplace(node->right);
      }
    }
  }

 public:
  TreeNode* sortedArrayToBST(const vector<int>& nums) {
    const size_t nums_size{nums.size()};

    if (!nums_size)
      return nullptr;

    if (1 == nums_size) {
      TreeNode* root_node = new TreeNode{nums[0]};
      return root_node;
    }

    if (2 == nums_size) {
      TreeNode* root_node = new TreeNode{nums[0]};
      root_node->left = new TreeNode{nums[1]};
      return root_node;
    }

    if (3 == nums_size) {
      TreeNode* root_node = new TreeNode{nums[1]};
      root_node->left = new TreeNode{nums[0]};
      root_node->right = new TreeNode{nums[2]};
      return root_node;
    }

    TreeNode* root_node = new TreeNode{nums[nums_size / 2]};

    for (int i = nums_size / 2 - 1; i >= 0; i--) {
      construct_height_balanced_bst(root_node, nums[i]);
    }

    for (size_t i{nums_size / 2 + 1}; i < nums_size; i++) {
      construct_height_balanced_bst(root_node, nums[i]);
    }

    return root_node;
  }

  vector<vector<int>> levelOrderTraversal(const TreeNode* root) {
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
  const vector<int> input{-10, -3, 0, 5, 9};
  unique_ptr<TreeNode> root_node{s.sortedArrayToBST(input)};
  const vector<vector<int>> output{s.levelOrderTraversal(root_node.get())};
  cout << "s.sortedArrayToBST({-10,-3,0,5,9}) -> " << output << '\n';

  return 0;
}
