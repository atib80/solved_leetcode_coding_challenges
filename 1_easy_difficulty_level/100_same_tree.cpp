/*
100. Leetcode coding challenge: Same tree

Given two binary trees, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical and
the nodes have the same value.

Example 1:

Input:     1         1
          / \       / \
         2   3     2   3

        [1,2,3],   [1,2,3]

Output: true

Example 2:

Input:     1         1
          /           \
         2             2

        [1,2,null],     [1,null,2]

Output: false

Example 3:

Input:     1         1
          / \       / \
         2   1     1   2

        [1,2,1],   [1,1,2]

Output: false
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
  bool isSameTree(const TreeNode* p, const TreeNode* q) {
    stack<const TreeNode*> left_tree{{p}}, right_tree{{q}};

    while (!left_tree.empty() && !right_tree.empty()) {
      const TreeNode* ltn{left_tree.top()};
      left_tree.pop();
      const TreeNode* rtn{right_tree.top()};
      right_tree.pop();

      if (!ltn && !rtn)
        continue;
      if (!ltn && rtn)
        return false;
      if (ltn && !rtn)
        return false;
      if (ltn->val != rtn->val)
        return false;
      left_tree.emplace(ltn->left);
      left_tree.emplace(ltn->right);
      right_tree.emplace(rtn->left);
      right_tree.emplace(rtn->right);
    }

    if (left_tree.empty() && right_tree.empty())
      return true;

    return false;
  }
};

int main() {
  Solution s{};
  TreeNode ltr1{1}, ltlch1{2}, ltrch1{3};
  ltr1.left = &ltlch1;
  ltr1.right = &ltrch1;
  TreeNode rtr1{1}, rtlch1{2}, rtrch1{3};
  rtr1.left = &rtlch1;
  rtr1.right = &rtrch1;

  TreeNode ltr2{1}, ltlch2{2};
  ltr2.left = &ltlch2;
  TreeNode rtr2{1}, rtrch2{2};
  rtr2.right = &rtrch2;

  TreeNode ltr3{1}, ltlch3{2}, ltrch3{1};
  ltr3.left = &ltlch3;
  ltr3.right = &ltrch3;
  TreeNode rtr3{1}, rtlch3{1}, rtrch3{2};
  rtr3.left = &rtlch3;
  rtr3.right = &rtrch3;

  cout << boolalpha << "s.isSameTree([1,2,3], [1,2,3]) -> "
       << s.isSameTree(&ltr1, &rtr1) << '\n'  // expected output: true
       << "s.isSameTree([1,2,null], [1,null,2]) -> "
       << s.isSameTree(&ltr2, &rtr2) << '\n'  // expected output: false
       << "s.isSameTree([1,2,1], [1,1,2]) -> " << s.isSameTree(&ltr3, &rtr3)
       << '\n'  // expected output: false
       << noboolalpha << '\n';

  return 0;
}
