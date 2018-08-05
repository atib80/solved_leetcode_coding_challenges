/*
98. Leetcode coding challenge: Validate binary search tree

Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

    The left subtree of a node contains only nodes with keys less than the
node's key. The right subtree of a node contains only nodes with keys greater
than the node's key. Both the left and right subtrees must also be binary search
trees.

Example 1:

Input:
    2
   / \
  1   3
Output: true

Example 2:

    5
   / \
  1   4
     / \
    3   6
Output: false
Explanation: The input is: [5,1,4,null,null,3,6]. The root node's value
             is 5 but its right child's value is 4.

*/

#include <climits>
#include <iomanip>
#include <iostream>
#include <unordered_set>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(const int x) : val{x}, left{}, right{} {}
};

class Solution {
  bool check_if_valid_bst(const TreeNode* root,
                          const int min_val,
                          const int max_val) {
    if (!root)
      return true;

    if (visited_numbers.count(root->val))
      return false;
    visited_numbers.insert(root->val);

    if (root->val < min_val || root->val > max_val)
      return false;

    return check_if_valid_bst(root->left, min_val, root->val) &&
           check_if_valid_bst(root->right, root->val, max_val);
  }

  unordered_set<int> visited_numbers{};

 public:
  bool isValidBST(const TreeNode* root) {
    visited_numbers.clear();
    return check_if_valid_bst(root, INT_MIN, INT_MAX);
  }
};

int main() {
  Solution s{};

  TreeNode root1{2}, lc1{1}, rc1{3};
  root1.left = &lc1;
  root1.right = &rc1;

  cout << boolalpha << "s.isValidBST([2,1,3]) -> " << s.isValidBST(&root1)
       << '\n';  // expected output: true

  TreeNode root2{5}, lc2{1}, rc2{4}, rc2_lc1{3}, rc2_rc1{6};
  root2.left = &lc2;
  root2.right = &rc2;
  rc2.left = &rc2_lc1;
  rc2.right = &rc2_rc1;

  cout << "s.isValidBST([5,1,4,nullptr,nullptr,3,6]) -> "
       << s.isValidBST(&root2) << '\n';  // expected output: false

  TreeNode root3{INT_MIN}, lc3{INT_MIN};
  root3.left = &lc3;
  cout << "s.isValidBST([INT_MIN, INT_MIN]) -> " << s.isValidBST(&root3)
       << '\n';  // expected output: false

  TreeNode root4{1};
  cout << "s.isValidBST([1]) -> " << s.isValidBST(&root4)
       << '\n';  // expected output: true

  return 0;
}
