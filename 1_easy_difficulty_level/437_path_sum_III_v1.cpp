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
#include <tuple>
#include <unordered_map>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(const int x) : val{x}, left{}, right{} {}
};

class Solution {
  template <typename T, typename U>
  static bool check_if_path_nodes_already_visited(
      unordered_map<T, vector<vector<T>>>& unique_paths,
      U&& path_nodes) {
    if (unique_paths.find(path_nodes[0]) != end(unique_paths)) {
      for (const auto& path : unique_paths.at(path_nodes[0])) {
        if (path == path_nodes)
          return true;
      }
    }

    unique_paths[path_nodes[0]].emplace_back(path_nodes);

    return false;
  }

 public:
  int pathSum(const TreeNode* root, const int sum) const {
    if (!root)
      return 0;

    int cnt{};
    queue<tuple<const TreeNode*, int, vector<const TreeNode*>>> q{
        {make_tuple(root, root->val, vector<const TreeNode*>{root})}};
    unordered_map<const TreeNode*, vector<vector<const TreeNode*>>>
        unique_paths{make_pair(root, vector<vector<const TreeNode*>>{{root}})};

    while (!q.empty()) {
      const TreeNode* node{get<0>(q.front())};
      const int current_sum{get<1>(q.front())};
      vector<const TreeNode*> path_nodes{move(get<2>(q.front()))};
      q.pop();

      if (sum == current_sum)
        cnt++;

      if (node->left) {
        path_nodes.emplace_back(node->left);
        if (!check_if_path_nodes_already_visited(unique_paths, path_nodes))
          q.emplace(make_tuple(node->left, current_sum + node->left->val,
                               path_nodes));
        path_nodes.pop_back();
        if (!check_if_path_nodes_already_visited(
                unique_paths, vector<const TreeNode*>{node->left}))
          q.emplace(make_tuple(node->left, node->left->val,
                               vector<const TreeNode*>{node->left}));
      }

      if (node->right) {
        path_nodes.emplace_back(node->right);
        if (!check_if_path_nodes_already_visited(unique_paths, path_nodes))
          q.emplace(make_tuple(node->right, current_sum + node->right->val,
                               move(path_nodes)));
        if (!check_if_path_nodes_already_visited(
                unique_paths, vector<const TreeNode*>{node->right}))
          q.emplace(make_tuple(node->right, node->right->val,
                               vector<const TreeNode*>{node->right}));
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
       << s.pathSum(&root1, 8) << '\n';  // expected output: 3

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

  TreeNode root4{0}, lc4{1}, rc4{1};
  root4.left = &lc4;
  root4.right = &rc4;

  cout << "s.pathSum([0, 1, 1], 1) -> " << s.pathSum(&root4, 1)
       << '\n';  // expected output: 4

  return 0;
}
