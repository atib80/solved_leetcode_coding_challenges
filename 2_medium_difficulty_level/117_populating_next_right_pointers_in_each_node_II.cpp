/*
117. Populating Next Right Pointers in Each Node II  (difficulty level: medium)

Given a binary tree

struct TreeLinkNode {
  TreeLinkNode *left;
  TreeLinkNode *right;
  TreeLinkNode *next;
}

Populate each next pointer to point to its next right node. If there is no next
right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

    You may only use constant extra space.
    Recursive approach is fine, implicit stack space does not count as extra
space for this problem.

Example:

Given the following binary tree,

     1
   /  \
  2    3
 / \    \
4   5    7

After calling your function, the tree should look like:

     1 -> NULL
   /  \
  2 -> 3 -> NULL
 / \    \
4-> 5 -> 7 -> NULL
*/

#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

// Definition for binary tree with next pointer.
struct TreeLinkNode {
  int val;
  TreeLinkNode *left, *right, *next;
  TreeLinkNode(const int x) : val{x}, left{}, right{}, next{} {}
};

class Solution {
 public:
  void connect(TreeLinkNode* root) const {
    if (!root)
      return;
    queue<TreeLinkNode*> qt{{root}};
    queue<TreeLinkNode*> ql{};

    while (!qt.empty()) {
      TreeLinkNode* src{qt.front()};
      qt.pop();
      if (src->left)
        ql.emplace(src->left);
      if (src->right)
        ql.emplace(src->right);
      src->next = nullptr;

      while (!qt.empty()) {
        TreeLinkNode* dst{qt.front()};
        qt.pop();
        if (dst->left)
          ql.emplace(dst->left);
        if (dst->right)
          ql.emplace(dst->right);
        src->next = dst;
        src = dst;
      }
      qt.swap(ql);
    }
  }

  vector<vector<const TreeLinkNode*>> levelOrder(const TreeLinkNode* root) {
    vector<vector<const TreeLinkNode*>> output{};

    if (!root)
      return output;
    queue<const TreeLinkNode*> qt{{root}};
    queue<const TreeLinkNode*> ql{};

    do {
      vector<const TreeLinkNode*> level_nodes{};
      while (!qt.empty()) {
        const TreeLinkNode* tn{qt.front()};
        qt.pop();
        level_nodes.emplace_back(tn);
        if (tn->left)
          ql.emplace(tn->left);
        if (tn->right)
          ql.emplace(tn->right);
      }
      qt.swap(ql);
      output.push_back(move(level_nodes));
    } while (!qt.empty());

    return output;
  }
};

int main() {
  Solution s{};

  TreeLinkNode root{1}, lc1{2}, rc1{3}, lc1_lc1{4}, lc1_rc1{5}, rc1_rc1{7};

  root.left = &lc1;
  root.right = &rc1;
  lc1.left = &lc1_lc1;
  lc1.right = &lc1_rc1;
  rc1.right = &rc1_rc1;

  s.connect(&root);

  const auto level_order_traversal{s.levelOrder(&root)};

  if (level_order_traversal.empty())
    cout << "[nullptr]";
  else {
    for (const auto& level : level_order_traversal) {
      cout << '[';

      for (size_t i{}; i < level.size(); i++)
        cout << level[i]->val << " -> ";
      cout << "nullptr";

      cout << "]\n";
    }
  }

  return 0;
}
