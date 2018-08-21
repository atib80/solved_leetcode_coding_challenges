/*
106. Leetcode coding challenge: Construct binary tree from inorder and postorder
traversal

Given inorder and postorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

For example, given

inorder = [9,3,15,20,7]
postorder = [9,15,7,20,3]

Return the following binary tree:

    3
   / \
  9  20
    /  \
   15   7
*/

#include <algorithm>
#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <string>
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
  ~TreeNode() {
    if (left) {
      delete left;
      left = nullptr;
    }

    if (right) {
      delete right;
      right = nullptr;
    }
  }
};

class Solution {
 public:
  TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    const size_t N{inorder.size()};
    if (N != postorder.size())
      return nullptr;

    reverse(begin(inorder), end(inorder));
    reverse(begin(postorder), end(postorder));
    stack<TreeNode*> s{};
    TreeNode* root{};
    size_t pi{}, ii{};
    bool last{};

    while (pi < N) {
      do {
        TreeNode* node{new TreeNode{postorder[pi]}};

        if (!s.empty()) {
          if (last) {
            s.top()->left = node;
            s.pop();
            last = false;
          } else
            s.top()->right = node;
        }

        if (!root)
          root = node;

        s.emplace(node);

      } while (postorder[pi++] != inorder[ii] && ii < N && pi < N);

      TreeNode* node{};

      while (!s.empty() && ii < N && inorder[ii] == s.top()->val) {
        node = s.top();
        s.pop();
        ii++;
      }

      if (node) {
        last = true;
        s.emplace(node);
      }
    }

    return root;
  }

  vector<int> preorder_traversal(const TreeNode* root) {
    vector<int> output{};

    if (!root)
      return output;

    queue<const TreeNode*> q{{root}};
    stack<const TreeNode*> s{};

    while (!q.empty()) {
      const TreeNode* current_node{q.front()};
      q.pop();

      if (!current_node) {
        if (!s.empty()) {
          q.emplace(s.top());
          s.pop();
        }
        continue;
      }

      output.emplace_back(current_node->val);

      q.emplace(current_node->left);
      s.emplace(current_node->right);
    }

    return output;
  }
};

int main() {
  Solution s{};

  vector<int> inorder_bt_elements{9, 3, 15, 20, 7};
  vector<int> postorder_bt_elements{9, 15, 7, 20, 3};
  unique_ptr<TreeNode> bt_root{
      s.buildTree(inorder_bt_elements, postorder_bt_elements)};
  const auto preorder_traversal_of_bt{s.preorder_traversal(bt_root.get())};
  cout << "s.buildTree([9,3,15,20,7], [9,15,7,20,3]) -> "
       << preorder_traversal_of_bt << '\n';  // expected output: [3,9,20,15,7]

  return 0;
}
