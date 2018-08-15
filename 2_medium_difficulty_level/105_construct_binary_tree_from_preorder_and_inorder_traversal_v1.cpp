/*
105. Leetcode coding challenge: Construct binary tree from preorder and inorder
traversal

Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

For example, given

preorder = [3,9,20,15,7]
inorder = [9,3,15,20,7]

Return the following binary tree:

    3
   / \
  9  20
    /  \
   15   7

*/

#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <vector>

using std::cout;
using std::ostream;
using std::queue;
using std::stack;
using std::unique_ptr;
using std::vector;

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

template <typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& data) {
  if (data.empty()) {
    os << "data is empty\n";
    return os;
  }

  os << "\n[\n";
  for (const auto& row : data)
    os << row;
  os << "\n]\n";

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
  TreeNode* buildTree(const vector<int>& preorder_elements,
                      const vector<int>& inorder_elements) {
    if (preorder_elements.size() != inorder_elements.size())
      return nullptr;
    return build(preorder_elements, 0, inorder_elements, 0,
                 preorder_elements.size());
  }

  TreeNode* build(const vector<int>& preorder_elements,
                  const int preorder_index,
                  const vector<int>& inorder_elements,
                  const int inorder_index,
                  const int len) {
    if (len <= 0)
      return nullptr;
    if (1 == len) {
      TreeNode* node = new TreeNode(preorder_elements[preorder_index]);
      return node;
    }
    int im = inorder_index;
    while (inorder_elements[im] != preorder_elements[preorder_index])
      im++;
    const int lLen{im - inorder_index};
    const int rLen{len - lLen - 1};
    TreeNode* node = new TreeNode(inorder_elements[im]);
    node->left = build(preorder_elements, preorder_index + 1, inorder_elements,
                       inorder_index, lLen);
    node->right = build(preorder_elements, preorder_index + lLen + 1,
                        inorder_elements, im + 1, rLen);
    return node;
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
  unique_ptr<TreeNode> bst_root{
      s.buildTree({3, 9, 20, 15, 7}, {9, 3, 15, 20, 7})};
  const auto preorder_traversal{s.preorder_traversal(bst_root.get())};
  cout << "s.preorder_traversal(bst_root) -> " << preorder_traversal
       << '\n';  // expected output: [3,9,20,15,7]
  const auto inorder_traversal{s.inorder_traversal(bst_root.get())};
  cout << "s.inorder_traversal(bst_root) -> " << inorder_traversal
       << '\n';  // expected output: [9,3,15,20,7]

  return 0;
}
