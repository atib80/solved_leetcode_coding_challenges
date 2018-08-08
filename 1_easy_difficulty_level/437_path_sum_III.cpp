/*
You are given a binary tree in which each node contains an integer value.

Find the number of paths that sum to a given value.

The path does not need to start or end at the root or a leaf, but it must go
downwards (traveling only from parent nodes to child nodes).

The tree has no more than 1,000 nodes and the values are in the range -1,000,000
to 1,000,000.

Example:

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

Return 3. The paths that sum to 8 are:

1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11
*/

#include <iostream>
#include <queue>
#include <utility>

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
  int pathSum(const TreeNode* root, const int sum) {
    if (!root)
      return 0;

    int cnt{};
    queue<pair<const TreeNode*, int>> q{{make_pair(root, root->val)}};

    while (!q.empty()) {
      const TreeNode* node{q.front().first};
      const int current_sum{q.front().second};
      q.pop();

      if (sum == current_sum)
        cnt++;
      if (node->left) {
        if (sum == current_sum + node->left->val)
          cnt++;
        else
          q.emplace(make_pair(node->left, current_sum + node->left->val));

        q.emplace(make_pair(node->left, node->left->val));
      }

      if (node->right) {
        if (sum == current_sum + node->right->val)
          cnt++;
        else
          q.emplace(make_pair(node->right, current_sum + node->right->val));

        q.emplace(make_pair(node->right, node->right->val));
      }
    }

    return cnt;
  }
};

int main() {
  Solution s{};

  TreeNode root1{10}, lc1{5}, rc1{-3}, lc1_lc1{3}, lc1_rc1{2}, lc1_lc1_lc1{3},
      lc1_lc1_rc1{-2}, lc1_rc1_rc1{1}, rc1_rc1{11};
  root1.left = &lc1;
  root1.right = &rc1;
  lc1.left = &lc1_lc1;
  lc1.right = &lc1_rc1;
  lc1_rc1.right = &lc1_rc1_rc1;
  lc1_lc1.left = &lc1_lc1_lc1;
  lc1_lc1.right = &lc1_lc1_rc1;
  rc1.right = &rc1_rc1;

  cout << "s.pathSum([10,5,-3,3,2,null,11,3,-2,null,1], 8) -> "
       << s.pathSum(&root1, 8) << '\n';

  // [1,null,2,null,3,null,4,null,5], 3

  TreeNode root2{1}, rc2{2}, rc2_rc2{3}, rc2_rc2_rc2{4}, rc2_rc2_rc2_rc2{5};
  root2.right = &rc2;
  rc2.right = &rc2_rc2;
  rc2_rc2.right = &rc2_rc2_rc2;
  rc2_rc2_rc2.right = &rc2_rc2_rc2_rc2;

  cout << "s.pathSum([1,null,2,null,3,null,4,null,5], 3) -> "
       << s.pathSum(&root2, 3) << '\n';

  return 0;
}
