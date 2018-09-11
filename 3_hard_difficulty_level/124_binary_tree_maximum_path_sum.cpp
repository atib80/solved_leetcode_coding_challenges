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
   / \
  9  20
    /  \
   15   7

Output: 42
*/

#include <climits>
#include <iostream>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  explicit TreeNode(const int x) : val{x}, left{}, right{} {}
};

class Solution {
  static void find_left_tree_maximum_path_sum(
      const TreeNode* node,
      int& maximum_left_tree_path_sum,
      const int current_left_tree_path_sum) {
    if (!node)
      return;

    if (current_left_tree_path_sum > maximum_left_tree_path_sum)
      maximum_left_tree_path_sum = current_left_tree_path_sum;

    if (node->left) {
      find_left_tree_maximum_path_sum(
          node->left, maximum_left_tree_path_sum,
          current_left_tree_path_sum + node->left->val);
      find_left_tree_maximum_path_sum(node->left, maximum_left_tree_path_sum,
                                      node->left->val);
    }

    if (node->right) {
      find_left_tree_maximum_path_sum(
          node->right, maximum_left_tree_path_sum,
          current_left_tree_path_sum + node->right->val);
      find_left_tree_maximum_path_sum(node->right, maximum_left_tree_path_sum,
                                      node->right->val);
    }
  }

  static void find_right_tree_maximum_path_sum(
      const TreeNode* node,
      int& maximum_right_tree_path_sum,
      const int current_right_tree_path_sum) {
    if (!node)
      return;

    if (current_right_tree_path_sum > maximum_right_tree_path_sum)
      maximum_right_tree_path_sum = current_right_tree_path_sum;

    if (node->left) {
      find_right_tree_maximum_path_sum(
          node->left, maximum_right_tree_path_sum,
          current_right_tree_path_sum + node->left->val);
      find_right_tree_maximum_path_sum(node->left, maximum_right_tree_path_sum,
                                       node->left->val);
    }

    if (node->right) {
      find_right_tree_maximum_path_sum(
          node->right, maximum_right_tree_path_sum,
          current_right_tree_path_sum + node->right->val);
      find_right_tree_maximum_path_sum(node->right, maximum_right_tree_path_sum,
                                       node->right->val);
    }
  }

  static void find_maximum_path_sum(const TreeNode* node,
                                    int& maximum_path_sum,
                                    const int current_path_sum) {
    if (current_path_sum > maximum_path_sum)
      maximum_path_sum = current_path_sum;

    if (node->left && node->right) {
      int maximum_left_tree_path_sum{}, maximum_right_tree_path_sum{};

      find_left_tree_maximum_path_sum(node->left, maximum_left_tree_path_sum,
                                      node->left->val);
      find_right_tree_maximum_path_sum(node->right, maximum_right_tree_path_sum,
                                       node->right->val);
      if (node->val > maximum_path_sum)
        maximum_path_sum = node->val;
      if (maximum_left_tree_path_sum > maximum_path_sum)
        maximum_path_sum = maximum_left_tree_path_sum;
      if (maximum_right_tree_path_sum > maximum_path_sum)
        maximum_path_sum = maximum_right_tree_path_sum;
      if (maximum_left_tree_path_sum + node->val > maximum_path_sum)
        maximum_path_sum = maximum_left_tree_path_sum + node->val;
      if (maximum_right_tree_path_sum + node->val > maximum_path_sum)
        maximum_path_sum = maximum_right_tree_path_sum + node->val;
      if (maximum_left_tree_path_sum + node->val + maximum_right_tree_path_sum >
          maximum_path_sum)
        maximum_path_sum = maximum_left_tree_path_sum + node->val +
                           maximum_right_tree_path_sum;
    }

    if (node->left) {
      find_maximum_path_sum(node->left, maximum_path_sum,
                            current_path_sum + node->left->val);
      find_maximum_path_sum(node->left, maximum_path_sum, node->left->val);
    }

    if (node->right) {
      find_maximum_path_sum(node->right, maximum_path_sum,
                            current_path_sum + node->right->val);
      find_maximum_path_sum(node->right, maximum_path_sum, node->right->val);
    }
  }

 public:
  int maxPathSum(const TreeNode* root) {
    if (!root)
      return 0;

    int maximum_path_sum{INT_MIN};

    find_maximum_path_sum(root, maximum_path_sum, root->val);

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

  return 0;
}
