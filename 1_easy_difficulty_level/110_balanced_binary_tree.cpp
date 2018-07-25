/*
110. Leetcode coding challenge: Balanced binary tree

Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as:

    a binary tree in which the depth of the two subtrees of every node never
differ by more than 1.

Example 1:

Given the following tree [3,9,20,null,null,15,7]:

    3
   / \
  9  20
    /  \
   15   7

Return true.

Example 2:

Given the following tree [1,2,2,3,3,null,null,4,4]:

       1
      / \
     2   2
    / \
   3   3
  / \
 4   4

 Return false.
*/

#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
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
  bool isBalanced(const TreeNode* root) {
    if (!root || (root && !root->left && !root->right))
      return true;

    queue<const TreeNode*> q{{root}};

    while (!q.empty()) {
      const TreeNode* node{q.front()};
      q.pop();

      if (node->left)
        q.emplace(node->left);
      if (node->right)
        q.emplace(node->right);

      int left_tree_height{};

      if (node->left) {
        queue<pair<const TreeNode*, int>> qh{{make_pair(node->left, 1)}};

        while (!qh.empty()) {
          const TreeNode* child_node{qh.front().first};
          const int height{qh.front().second};
          qh.pop();

          if (!child_node->left && !child_node->right) {
            if (height > left_tree_height)
              left_tree_height = height;
            continue;
          }

          if (child_node->left)
            qh.emplace(make_pair(child_node->left, height + 1));
          if (child_node->right)
            qh.emplace(make_pair(child_node->right, height + 1));
        }
      }

      int right_tree_height{};

      if (node->right) {
        queue<pair<const TreeNode*, int>> qh{{make_pair(node->right, 1)}};

        while (!qh.empty()) {
          const TreeNode* child_node{qh.front().first};
          const int height{qh.front().second};
          qh.pop();

          if (!child_node->left && !child_node->right) {
            if (height > right_tree_height)
              right_tree_height = height;
            continue;
          }

          if (child_node->left)
            qh.emplace(make_pair(child_node->left, height + 1));
          if (child_node->right)
            qh.emplace(make_pair(child_node->right, height + 1));
        }
      }

      if (abs(left_tree_height - right_tree_height) > 1)
        return false;
    }

    return true;
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

  TreeNode tr2{1}, lch_2{2}, rch_2{2};
  tr2.left = &lch_2;
  tr2.right = &rch_2;
  TreeNode lch_lch_2{3}, lch_rch_2{3};
  lch_2.left = &lch_lch_2;
  lch_2.right = &lch_rch_2;
  TreeNode lch_lch_lch_2{4}, lch_lch_rch_2{4};
  lch_lch_2.left = &lch_lch_lch_2;
  lch_lch_2.right = &lch_lch_rch_2;

  cout << boolalpha << "s.isBalanced({3,9,20,null,null,15,7}) -> "
       << s.isBalanced(&tr1) << '\n'
       << "s.isBalanced({1,2,2,3,3,null,null,4,4}) -> " << s.isBalanced(&tr2)
       << '\n'
       << noboolalpha;

  return 0;
}