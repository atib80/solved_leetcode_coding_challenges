/*
124. Binary tree maximum path sum (difficulty level: hard)

Given a non-empty binary tree, find the maximum path sum.

For this problem, a path is defined as any sequence of nodes from some starting
node to any node in the tree along the parent-child connections. The path must
contain at least one node and does not need to go through the root.

Example 1:

Input: [1,2,3]

       1
      / \
     2   3

Output: 6

Example 2:

Input: [-10,9,20,null,null,15,7]

    -10
   /   \
  9    20
      /  \
     15   7

Output: 42

          5
        4   8
      11  13  4
     7  2       1
*/

#include <algorithm>
#include <climits>
#include <iostream>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(const int x) : val{x}, left{}, right{} {}
  ~TreeNode() {
    if (left)
      delete left;
    if (right)
      delete right;
  }
};

class Solution {
  void find_sub_tree_maximum_path_sum(TreeNode* node,
                                      int& maximum_path_sum,
                                      int& maximum_sub_tree_path_sum,
                                      const int current_sub_tree_path_sum,
                                      const int current_path_sum) {
    if (current_path_sum > maximum_path_sum)
      maximum_path_sum = current_path_sum;

    if (current_sub_tree_path_sum > maximum_sub_tree_path_sum)
      maximum_sub_tree_path_sum = current_sub_tree_path_sum;

    if (node->left && node->right) {
      int left_tree_path_sum{INT_MIN}, right_tree_path_sum{INT_MIN};

      find_sub_tree_maximum_path_sum(node->left, maximum_path_sum,
                                     left_tree_path_sum, node->left->val,
                                     node->left->val);
      find_sub_tree_maximum_path_sum(node->right, maximum_path_sum,
                                     right_tree_path_sum, node->right->val,
                                     node->right->val);
      if (node->val > maximum_path_sum)
        maximum_path_sum = node->val;
      if (left_tree_path_sum > maximum_path_sum)
        maximum_path_sum = left_tree_path_sum;
      if (right_tree_path_sum > maximum_path_sum)
        maximum_path_sum = right_tree_path_sum;
      if (left_tree_path_sum + node->val > maximum_path_sum)
        maximum_path_sum = left_tree_path_sum + node->val;
      if (right_tree_path_sum + node->val > maximum_path_sum)
        maximum_path_sum = right_tree_path_sum + node->val;
      if (left_tree_path_sum + node->val + right_tree_path_sum >
          maximum_path_sum)
        maximum_path_sum = left_tree_path_sum + node->val + right_tree_path_sum;

      const int prev_max_path_sum{current_sub_tree_path_sum - node->val};

      node->val =
          max(left_tree_path_sum + node->val, right_tree_path_sum + node->val);
      if (prev_max_path_sum + node->val > maximum_sub_tree_path_sum)
        maximum_sub_tree_path_sum = prev_max_path_sum + node->val;

      // delete node->left;
      node->left = nullptr;
      // delete node->right;
      node->right = nullptr;

    } else {
      if (node->left) {
        find_sub_tree_maximum_path_sum(
            node->left, maximum_path_sum, maximum_sub_tree_path_sum,
            current_sub_tree_path_sum + node->left->val,
            current_path_sum + node->left->val);
        find_sub_tree_maximum_path_sum(
            node->left, maximum_path_sum, maximum_sub_tree_path_sum,
            current_sub_tree_path_sum + node->left->val, node->left->val);
      }

      if (node->right) {
        find_sub_tree_maximum_path_sum(
            node->right, maximum_path_sum, maximum_sub_tree_path_sum,
            current_sub_tree_path_sum + node->right->val,
            current_path_sum + node->right->val);
        find_sub_tree_maximum_path_sum(
            node->right, maximum_path_sum, maximum_sub_tree_path_sum,
            current_sub_tree_path_sum + node->right->val, node->right->val);
      }
    }
  }

 public:
  int maxPathSum(TreeNode* root) {
    if (!root)
      return 0;

    int maximum_path_sum{INT_MIN}, maximum_left_tree_path_sum{INT_MIN},
        maximum_right_tree_path_sum{INT_MIN};

    if (root->left)
      find_sub_tree_maximum_path_sum(root->left, maximum_path_sum,
                                     maximum_left_tree_path_sum,
                                     root->left->val, root->left->val);
    if (root->right)
      find_sub_tree_maximum_path_sum(root->right, maximum_path_sum,
                                     maximum_right_tree_path_sum,
                                     root->right->val, root->right->val);
    if (root->val > maximum_path_sum)
      maximum_path_sum = root->val;
    if (root->left && maximum_left_tree_path_sum > maximum_path_sum)
      maximum_path_sum = maximum_left_tree_path_sum;
    if (root->right && maximum_right_tree_path_sum > maximum_path_sum)
      maximum_path_sum = maximum_right_tree_path_sum;
    if (root->left && maximum_left_tree_path_sum + root->val > maximum_path_sum)
      maximum_path_sum = maximum_left_tree_path_sum + root->val;
    if (root->right &&
        maximum_right_tree_path_sum + root->val > maximum_path_sum)
      maximum_path_sum = maximum_right_tree_path_sum + root->val;
    if (root->left && root->right &&
        maximum_left_tree_path_sum + root->val + maximum_right_tree_path_sum >
            maximum_path_sum)
      maximum_path_sum =
          maximum_left_tree_path_sum + root->val + maximum_right_tree_path_sum;

    return maximum_path_sum;
  }
};

int main() {
  Solution s{};

  TreeNode root1{1}, lc1{2}, rc1{3};
  root1.left = &lc1;
  root1.right = &rc1;
  cout << "s.maxPathSum([1,2,3]) -> " << s.maxPathSum(&root1)
       << '\n';  // expected output: 6

  TreeNode root2{-10}, lc2{9}, rc2{20}, rc2_lc2{15}, rc2_rc2{7};
  root2.left = &lc2;
  root2.right = &rc2;
  rc2.left = &rc2_lc2;
  rc2.right = &rc2_rc2;
  cout << "s.maxPathSum([-10,9,20,null,null,15,7]) -> " << s.maxPathSum(&root2)
       << '\n';  // expected output: 42

  TreeNode root3{5}, lc3{4}, rc3{8}, lc3_lc3{11}, lc3_lc3_lc3{7},
      lc3_lc3_rc3{2}, rc3_lc3{13}, rc3_rc3{4}, rc3_rc3_rc3{1};
  root3.left = &lc3;
  lc3.left = &lc3_lc3;
  root3.right = &rc3;
  lc3_lc3.left = &lc3_lc3_lc3;
  lc3_lc3.right = &lc3_lc3_rc3;
  rc3.left = &rc3_lc3;
  rc3.right = &rc3_rc3;
  rc3_rc3.right = &rc3_rc3_rc3;
  cout << "s.maxPathSum([5,4,8,11,null,13,4,7,2,null,null,null,1]) -> "
       << s.maxPathSum(&root3) << '\n';  // expected output: 48

  TreeNode root4{1}, lc4{-2}, rc4{-3}, lc4_lc4{1}, lc4_rc4{3}, lc4_lc4_lc4{-1},
      lc4_lc4_rc4{-2}, rc4_lc4{-2};
  root4.left = &lc4;
  root4.right = &rc4;
  lc4.left = &lc4_lc4;
  lc4.right = &lc4_rc4;
  lc4_lc4.left = &lc4_lc4_lc4;
  lc4_lc4.right = &lc4_lc4_rc4;
  rc4.left = &rc4_lc4;
  cout << "s.maxPathSum([1,-2,-3,1,3,-2,null,-1,-2]) -> "
       << s.maxPathSum(&root4) << '\n';  // expected output: 3

  TreeNode root5{-3};
  cout << "s.maxPathSum([-3]) -> " << s.maxPathSum(&root5)
       << '\n';  // expected output: -3

  TreeNode root6{-2}, lc6{1};
  root6.left = &lc6;
  cout << "s.maxPathSum([-2,1]) -> " << s.maxPathSum(&root6)
       << '\n';  // expected output: 1

  return 0;
}
