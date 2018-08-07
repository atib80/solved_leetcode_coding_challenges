/*
Given a binary tree, return the zigzag level order traversal of its nodes'
values. (ie, from left to right, then right to left for the next level and
alternate between).

For example:
Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7

return its zigzag level order traversal as:

[
  [3],
  [20,9],
  [15,7]
]
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& data) {
  if (data.empty()) {
    os << "data is empty";
    return os;
  }
  os << "  [";
  for (size_t i{}; i < data.size() - 1; i++)
    os << data[i] << ',';
  os << data.back() << ']';
  return os;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& data) {
  if (data.empty()) {
    os << "data is empty";
    return os;
  }

  os << "\n[\n";
  for (const auto& row : data)
    os << row << '\n';
  os << "]\n";

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
 public:
  vector<vector<int>> zigzagLevelOrder(const TreeNode* root) {
    vector<vector<int>> result{};

    if (!root)
      return result;
    queue<const TreeNode*> qt{{root}};
    queue<const TreeNode*> ql{};
    vector<int> level_nodes{};
    bool reverse_dir{};

    do {
      level_nodes.clear();
      while (!qt.empty()) {
        const TreeNode* tn{qt.front()};
        qt.pop();
        level_nodes.emplace_back(tn->val);
        if (tn->left)
          ql.emplace(tn->left);
        if (tn->right)
          ql.emplace(tn->right);
      }
      qt.swap(ql);
      if (reverse_dir)
        reverse(begin(level_nodes), end(level_nodes));
      result.emplace_back(move(level_nodes));
      reverse_dir = !reverse_dir;

    } while (!qt.empty());

    return result;
  }
};

int main() {
  Solution s{};

  TreeNode root1{3}, lc1{9}, rc1{20}, rc1_lc1{15}, rc1_rc1{7};
  root1.left = &lc1;
  root1.right = &rc1;
  rc1.left = &rc1_lc1;
  rc1.right = &rc1_rc1;

  const auto bt_zigzag_level_order_traversal{s.zigzagLevelOrder(&root1)};
  cout << "s.zigzagLevelOrder([3, 9, 20, null, null, 15, 7]) -> "
       << bt_zigzag_level_order_traversal << '\n';

  return 0;
}
