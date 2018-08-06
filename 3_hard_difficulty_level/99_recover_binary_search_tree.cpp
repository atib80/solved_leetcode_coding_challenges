/*
99. Leetcode coding challenge: Recover binary search tree

Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Example 1:

Input: [1,3,null,null,2]

   1
  /
 3
  \
   2

Output: [3,1,null,null,2]

   3
  /
 1
  \
   2

Example 2:

Input: [3,1,4,null,null,2]

  3
 / \
1   4
   /
  2

Output: [2,1,4,null,null,3]

  2
 / \
1   4
   /
  3

Follow up:

    A solution using O(n) space is pretty straight forward.
    Could you devise a constant space solution?

*/

#include <algorithm>
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

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(const int x) : val{x}, left{}, right{} {}
};

class Solution {
  TreeNode *first, *second, *prev;

  void traverse_and_recover_bst(TreeNode* root) {
    if (!root)
      return;
    traverse_and_recover_bst(root->left);

    if (prev && prev->val >= root->val) {
      if (!first)
        first = prev;
      second = root;
    }
    prev = root;
    traverse_and_recover_bst(root->right);
  }

 public:
  void recoverTree(TreeNode* root) {
    if (!root)
      return;
    first = second = prev = nullptr;
    traverse_and_recover_bst(root);
    swap(first->val, second->val);
  }

  vector<int> inorder_traversal(const TreeNode* root) {
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

  TreeNode root1{1}, lc1{3}, lc1_rc1{2};
  root1.left = &lc1;
  lc1.right = &lc1_rc1;

  s.recoverTree(&root1);
  const auto bst_elements1{s.inorder_traversal(&root1)};
  cout << "s.recoverTree([1, 3, null, null, 2]) -> " << bst_elements1 << '\n';

  TreeNode root2{3}, lc2{1}, rc2{4}, rc2_lc1{2};
  root2.left = &lc2;
  root2.right = &rc2;
  rc2.left = &rc2_lc1;

  s.recoverTree(&root2);
  const auto bst_elements2{s.inorder_traversal(&root2)};
  cout << "s.recoverTree([3, 1, 4, null, null, 2]) -> " << bst_elements2
       << '\n';

  return 0;
}
