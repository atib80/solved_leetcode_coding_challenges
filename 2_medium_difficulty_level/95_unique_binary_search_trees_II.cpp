/*
95. Leetcode coding challenge: Unique binary search trees II

Given an integer n, generate all structurally unique BST's (binary search trees)
that store values 1 ... n.

Example:

Input: 3
Output:
[
  [1,null,3,2],
  [3,2,null,1],
  [3,1,null,null,2],
  [2,1,3],
  [1,null,2,null,3]
]
Explanation:
The above output corresponds to the 5 unique BST's shown below:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_set>
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
  static size_t factorial(const size_t n) {
    if (n < 2)
      return 1;

    size_t result{n};
    for (size_t i{n - 1}; i > 1; i--)
      result *= i;
    return result;
  }

  bool insert_node_with_value(TreeNode*& root, const int value) {
    if (value < root->val) {
      if (!root->left) {
        root->left = new TreeNode(value);
        return true;
      } else if (insert_node_with_value(root->left, value))
        return true;
    } else {
      if (!root->right) {
        root->right = new TreeNode(value);
        return true;
      } else if (insert_node_with_value(root->right, value))
        return true;
    }

    return false;
  }

 public:
  vector<TreeNode*> generateTrees(const int n) {
    if (!n)
      return {};
    if (1 == n) {
      TreeNode* root = new TreeNode{1};
      return {root};
    }

    const int min_value{min(1, n)};
    const size_t dim{static_cast<size_t>(abs(n - 1) + 1)};
    const size_t permutation_count{factorial(dim)};

    vector<TreeNode*> binary_search_trees{};
    binary_search_trees.reserve(permutation_count);
    vector<int> set(dim);

    for (size_t i{}; i < dim; i++)
      set[i] = min_value + i;

    unordered_set<string> already_created_binary_search_trees{};

    do {
      TreeNode* root = new TreeNode{set.front()};
      for (size_t i{1}; i < dim; i++)
        insert_node_with_value(root, set[i]);

      const string index{preorder_traversal(root)};

      if (!already_created_binary_search_trees.count(index)) {
        binary_search_trees.emplace_back(root);
        already_created_binary_search_trees.insert(index);
      } else
        delete root;

    } while (next_permutation(begin(set), end(set)));

    return binary_search_trees;
  }

  string preorder_traversal(const TreeNode* root) {
    ostringstream oss{};
    queue<const TreeNode*> q({root});
    stack<const TreeNode*> s{};

    oss << '[';

    while (!q.empty()) {
      const TreeNode* current_node{q.front()};
      q.pop();

      if (!current_node) {
        oss << "null,";
        if (!s.empty()) {
          q.emplace(s.top());
          s.pop();
        }
        continue;
      }

      oss << current_node->val << ',';
      q.emplace(current_node->left);
      s.emplace(current_node->right);
    }

    string output{oss.str()};
    output.back() = ']';
    return output;
  }
};

int main() {
  Solution s{};

  vector<TreeNode*> generated_bst0{s.generateTrees(0)};
  cout << "s.generated_bst(0) -> \n";
  for (auto& root : generated_bst0) {
    const string bst_str{s.preorder_traversal(root)};
    cout << bst_str << '\n';
    delete root;
    root = nullptr;
  }

  vector<TreeNode*> generated_bst1{s.generateTrees(1)};
  cout << "\ns.generated_bst(1) -> \n";
  for (auto& root : generated_bst1) {
    const string bst_str{s.preorder_traversal(root)};
    cout << bst_str << '\n';
    delete root;
    root = nullptr;
  }

  vector<TreeNode*> generated_bst2{s.generateTrees(2)};
  cout << "\ns.generated_bst(3) -> \n";
  for (auto& root : generated_bst2) {
    const string bst_str{s.preorder_traversal(root)};
    cout << bst_str << '\n';
    delete root;
    root = nullptr;
  }

  vector<TreeNode*> generated_bst3{s.generateTrees(3)};
  cout << "\ns.generated_bst(3) -> \n";
  for (auto& root : generated_bst3) {
    const string bst_str{s.preorder_traversal(root)};
    cout << bst_str << '\n';
    delete root;
    root = nullptr;
  }

  vector<TreeNode*> generated_bst4{s.generateTrees(4)};
  cout << "\ns.generated_bst(4) -> \n";
  for (auto& root : generated_bst4) {
    const string bst_str{s.preorder_traversal(root)};
    cout << bst_str << '\n';
    delete root;
    root = nullptr;
  }

  vector<TreeNode*> generated_bst5{s.generateTrees(5)};
  cout << "\ns.generated_bst(5) -> \n";
  for (auto& root : generated_bst5) {
    const string bst_str{s.preorder_traversal(root)};
    cout << bst_str << '\n';
    delete root;
    root = nullptr;
  }

  return 0;
}
