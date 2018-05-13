/*
Leetcode coding challenge: Merge k sorted lists

Merge k sorted linked lists and return it as one sorted list. Analyze and
describe its complexity.

Example:

Input:
[
  1->4->5,
  1->3->4,
  2->6
]
Output: 1->1->2->3->4->4->5->6
*/

#include <algorithm>
#include <iostream>
#include <vector>

struct ListNode {
  int val;
  ListNode* next;
  ListNode(const int x) : val{x}, next{} {}
};

class Solution {
 public:
  ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    std::vector<ListNode*> list_nodes{};

    for (ListNode* node : lists) {
      while (node) {
        list_nodes.emplace_back(node);
        node = node->next;
      }
    }

    if (list_nodes.empty())
      return nullptr;

    std::sort(std::begin(list_nodes), std::end(list_nodes),
              [](ListNode* lhs, ListNode* rhs) {

                return lhs->val < rhs->val;

              });

    ListNode* head{list_nodes[0]};
    ListNode* next{head};

    for (size_t i{1}; i < list_nodes.size(); i++) {
      next->next = list_nodes[i];
      next = next->next;
    }

    next->next = nullptr;

    return head;
  }
};

int main() {
  
  return 0;
}
