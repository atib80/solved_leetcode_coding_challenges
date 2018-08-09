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
  void find_all_paths_for_specified_sum(const TreeNode* root,
                                        vector<int>& path,
                                        size_t& path_cnt,
                                        const int sum) {
    if (!root)
      return;

    path.emplace_back(root->val);
    find_all_paths_for_specified_sum(root->left, path, path_cnt, sum);
    find_all_paths_for_specified_sum(root->right, path, path_cnt, sum);

    int current_sum{};
    for (int i = path.size() - 1; i >= 0; i--) {
      current_sum += path[i];

      if (current_sum == sum)
        path_cnt++;
    }

    path.pop_back();
  }

 public:
  int pathSum(const TreeNode* root, const int sum) {
    if (!root)
      return 0;

    vector<int> path{};
    size_t path_cnt{};
    find_all_paths_for_specified_sum(root, path, path_cnt, sum);

    return path_cnt;
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
       << s.pathSum(&root1, 8) << '\n';  // expected output: 3

  // [1,null,2,null,3,null,4,null,5], 3

  TreeNode root2{1}, rc2{2}, rc2_rc2{3}, rc2_rc2_rc2{4}, rc2_rc2_rc2_rc2{5};
  root2.right = &rc2;
  rc2.right = &rc2_rc2;
  rc2_rc2.right = &rc2_rc2_rc2;
  rc2_rc2_rc2.right = &rc2_rc2_rc2_rc2;

  cout << "s.pathSum([1,null,2,null,3,null,4,null,5], 3) -> "
       << s.pathSum(&root2, 3) << '\n';  // expected output: 2

  // [1,-2,-3,1,3,-2,null,-1], 3
  TreeNode root3{1}, lc3{-2}, rc3{-3}, lc3_lc3{1}, lc3_rc3{3}, rc3_lc3{-2},
      lc3_lc3_lc3{-1};
  root3.left = &lc3;
  root3.right = &rc3;
  lc3.left = &lc3_lc3;
  lc3.right = &lc3_rc3;
  rc3.left = &rc3_lc3;
  lc3_lc3.left = &lc3_lc3_lc3;

  cout << "s.pathSum([1,-2,-3,1,3,-2,null,-1], 3) -> " << s.pathSum(&root3, 3)
       << '\n';  // expected output: 1

  // [0, 1, 1], 1
  TreeNode root4{0}, lc4{1}, rc4{1};
  root4.left = &lc4;
  root4.right = &rc4;

  cout << "s.pathSum([0, 1, 1], 1) -> " << s.pathSum(&root4, 1)
       << '\n';  // expected output: 4

  return 0;
}
