/*
Given a singly linked list where elements are sorted in ascending order, convert
it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in
which the depth of the two subtrees of every node never differ by more than 1.

Example:

Given the sorted linked list: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following
height balanced BST:

      0
     / \
   -3   9
   /   /
 -10  5
*/

#include <iostream>
#include <memory>
#include <queue>
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

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode* next;
  ListNode(const int x) : val{x}, next{} {}
};

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
  static TreeNode* construct_height_balanced_bst(
      const vector<int>& sorted_numbers,
      const int start,
      const int end) {
    if (start > end)
      return nullptr;

    const int middle{(start + end) / 2};

    TreeNode* root{new TreeNode{sorted_numbers[middle]}};

    root->left =
        construct_height_balanced_bst(sorted_numbers, start, middle - 1);

    root->right =
        construct_height_balanced_bst(sorted_numbers, middle + 1, end);

    return root;
  }

 public:
  TreeNode* sortedListToBST(const ListNode* head) {
    if (!head)
      return nullptr;
    if (head && !head->next)
      return new TreeNode{head->val};
    vector<int> bst_values{};
    const ListNode* next{head};
    do {
      bst_values.emplace_back(next->val);
      next = next->next;
    } while (next);

    TreeNode* bst_root{
        construct_height_balanced_bst(bst_values, 0, bst_values.size() - 1)};

    return bst_root;
  }

  vector<int> inorderTraversal(const TreeNode* root) {
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

  vector<ListNode> input{ListNode{-10}, ListNode{-3}, ListNode{0}, ListNode{5},
                         ListNode{9}};
  for (size_t i{1}; i < input.size(); i++)
    input[i - 1].next = &input[i];

  unique_ptr<TreeNode> bst_root{s.sortedListToBST(&input[0])};
  auto inorder_traversal{s.inorderTraversal(bst_root.get())};
  cout << "s.sortedListToBST([-10,-3,0,5,9]) -> " << inorder_traversal << '\n';

  input.assign({ListNode{1}, ListNode{2}, ListNode{3}});
  for (size_t i{1}; i < input.size(); i++)
    input[i - 1].next = &input[i];

  bst_root.reset(s.sortedListToBST(&input[0]));
  inorder_traversal = s.inorderTraversal(bst_root.get());
  cout << "s.sortedListToBST([1,2,3]) -> " << inorder_traversal << '\n';

  input.assign({ListNode{1}, ListNode{2}});
  input[0].next = &input[1];

  bst_root.reset(s.sortedListToBST(&input[0]));
  inorder_traversal = s.inorderTraversal(bst_root.get());
  cout << "s.sortedListToBST([1,2]) -> " << inorder_traversal << '\n';

  return 0;
}
