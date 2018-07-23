/*
101. Leetcode coding challenge: Symmetric tree

Given a binary tree, check whether it is a mirror of itself (ie, symmetric
around its center).

For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3

But the following [1,2,2,null,3,null,3] is not:

    1
   / \
  2   2
   \   \
   3    3

Note:
Bonus points if you could solve it both recursively and iteratively.
*/

#include <iomanip>
#include <iostream>
#include <stack>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(const int x) : val{x}, left{}, right{} {}
};

class Solution {
 public:
  bool isSymmetric(const TreeNode* root) {
    stack<const TreeNode*> left_node{{root}};
    stack<const TreeNode*> right_node{{root}};

    while (!left_node.empty() && !right_node.empty()) {
      const TreeNode* ltn{left_node.top()};
      left_node.pop();
      const TreeNode* rtn{right_node.top()};
      right_node.pop();

      if (!ltn && !rtn)
        continue;
      if (!ltn && rtn)
        return false;
      if (ltn && !rtn)
        return false;
      if (ltn->val != rtn->val)
        return false;
      left_node.emplace(ltn->left);
      left_node.emplace(ltn->right);
      right_node.emplace(rtn->right);
      right_node.emplace(rtn->left);
    }

    if (left_node.empty() && right_node.empty())
      return true;

    return false;
  }
};

int main() {
  Solution s{};

  TreeNode tr1{1}, lt_lch_1{2}, lt_rch_1{2};
  tr1.left = &lt_lch_1;
  tr1.right = &lt_rch_1;
  TreeNode lt_lch_lch_1{3}, lt_lch_rch_1{4}, lt_rch_lch_1{4}, lt_rch_rch_1{3};
  lt_lch_1.left = &lt_lch_lch_1;
  lt_lch_1.right = &lt_lch_rch_1;
  lt_rch_1.left = &lt_rch_lch_1;
  lt_rch_1.right = &lt_rch_rch_1;

  TreeNode tr2{1}, lt_lch_2{2}, lt_rch_2{2};
  tr2.left = &lt_lch_2;
  tr2.right = &lt_rch_2;
  TreeNode lt_lch_rch_2{3}, lt_rch_rch_2{3};
  lt_lch_2.right = &lt_lch_rch_2;
  lt_rch_2.right = &lt_rch_rch_2;

  cout << boolalpha << "s.isSymmetric([1,2,2,3,4,4,3]) -> "
       << s.isSymmetric(&tr1) << '\n'  // expected output: true
       << "s.isSymmetric([1,2,2,null,3,null,3]) -> " << s.isSymmetric(&tr2)
       << '\n'  // expected output: false
       << noboolalpha << '\n';

  return 0;
}
