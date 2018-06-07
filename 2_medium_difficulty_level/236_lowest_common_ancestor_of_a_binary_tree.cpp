/*
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in
the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is
defined between two nodes p and q as the lowest node in T that has both p and q
as descendants (where we allow a node to be a descendant of itself).”

Given the following binary search tree:  root = [3,5,1,6,2,0,8,null,null,7,4]

        _______3______
       /              \
    ___5__          ___1__
   /      \        /      \
   6      _2       0       8
         /  \
         7   4

         1. 3,5 <-> 3,5,2,4
         2. 3,5 <-> 3,5|2,4|
         3. 3,5 <-> 3,5
         4. traversing the 2 vectors backward return the first TreeNode pointer
that's present in both vectors at the same index

Example 1:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of of nodes 5 and 1 is 3.

Example 2:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of
itself according to the LCA definition.

Note:

  All of the nodes' values will be unique.
  p and q are different and both values will exist in the binary tree.

*/

#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
  const int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(const int x) : val{x}, left{}, right{} {}
};

class Solution {
 public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    bool p_node_found{}, q_node_found{};
    vector<TreeNode*> visited_nodes_p{};
    vector<TreeNode*> visited_nodes_q{};
    queue<vector<TreeNode*>> que{{vector<TreeNode*>{root}}};

    if (!root)
      return nullptr;

    while (!que.empty()) {
      vector<TreeNode*> tree_nodes{move(que.front())};
      que.pop();

      if (p_node_found && q_node_found)
        break;

      TreeNode* current_node{tree_nodes.back()};

      if (!p_node_found && current_node->val == p->val) {
        p_node_found = true;
        if (q_node_found) {
          visited_nodes_p = move(tree_nodes);
          break;
        }
        visited_nodes_p = tree_nodes;
      }

      if (!q_node_found && current_node->val == q->val) {
        q_node_found = true;
        if (p_node_found) {
          visited_nodes_q = move(tree_nodes);
          break;
        }

        visited_nodes_q = tree_nodes;
      }

      if (current_node->left) {
        tree_nodes.emplace_back(current_node->left);
        if (!current_node->right) {
          que.emplace(move(tree_nodes));
          continue;
        } else {
          que.emplace(tree_nodes);
          tree_nodes.pop_back();
        }
      }

      if (current_node->right) {
        tree_nodes.emplace_back(current_node->right);
        que.emplace(move(tree_nodes));
      }
    }

    const size_t p_nodes_size{visited_nodes_p.size()},
        q_nodes_size{visited_nodes_q.size()};

    const vector<TreeNode*>& shortesth_path_nodes{
        p_nodes_size <= q_nodes_size ? visited_nodes_p : visited_nodes_q};

    const vector<TreeNode*>& longest_path_nodes{
        p_nodes_size > q_nodes_size ? visited_nodes_p : visited_nodes_q};

    unordered_set<TreeNode*> shortesth_path_nodes_set(
        begin(shortesth_path_nodes), end(shortesth_path_nodes));

    for (int i = longest_path_nodes.size() - 1; i >= 0; i--) {
      if (shortesth_path_nodes_set.count(longest_path_nodes[i]))
        return longest_path_nodes[i];
    }

    return nullptr;
  }
};

int main() {
  Solution s{};
  TreeNode root{1};
  TreeNode left{2};
  TreeNode right{3};
  TreeNode left_right{4};
  root.left = &left;
  root.right = &right;
  left.right = &left_right;

  // input: ([1, 2, 3, nullptr, 4], 4, 1)
  const TreeNode* result{s.lowestCommonAncestor(&root, &left_right, &root)};

  if (result)
    cout << "s.lowestCommonAncestor(&root, &left_right, &root)->val = "
         << result->val << '\n';  // expected output: 1
  else
    cout
        << "s.lowestCommonAncestor(&root, &left_right, &root) -> nullptr\n";  // expected output: 1

  return 0;
}
