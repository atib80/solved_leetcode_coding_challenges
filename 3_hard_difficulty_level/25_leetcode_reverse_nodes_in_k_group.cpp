/*
Leetcode coding challenge: Reverse nodes in k group

Given a linked list, reverse the nodes of a linked list k at a time and return
its modified list. k is a positive integer and is less than or equal to the
length of the linked list. If the number of nodes is not a multiple of k then
left-out nodes in the end should remain as it is.

Example:

Given this linked list: 1->2->3->4->5
For k = 2, you should return: 2->1->4->3->5
For k = 3, you should return: 3->2->1->4->5

Note:
Only constant extra memory is allowed.
You may not alter the values in the list's nodes, only nodes itself may be
changed.
*/

#include <iostream>
#include <stack>
#include <vector>

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode* next;
  ListNode(const int x) : val{x}, next{} {}
};

class Solution {
 public:
  ListNode* reverseKGroup(ListNode* head, int k) {
    if (!head || nullptr == head->next)
      return head;
    k--;

    std::stack<ListNode*> s{};

    ListNode* updated_head{};
    ListNode* last{head};
    ListNode* prev_end{};

    while (true) {
      for (int i{}; i < k; i++) {
        if (!last) {
          if (!updated_head)
            return head;
          return updated_head;
        }
        s.emplace(last);
        last = last->next;
      }

      if (!last) {
        if (!updated_head)
          return head;
        return updated_head;
      }

      if (!updated_head)
        updated_head = last;

      ListNode* next_start{last->next};

      if (prev_end) {
        prev_end->next = last;
      }

      while (!s.empty()) {
        ListNode* current{s.top()};
        s.pop();
        last->next = current;
        last = current;
      }

      prev_end = last;
      last->next = next_start;
      last = next_start;
    }

    return updated_head;
  }
};

int main() {

  // Given this linked list: 1->2->3->4->5->6->7->8->9-10
  // For k = 2
  // returned ListNode* after processing input singly-linked list should look like the following: 
  // 2->1->4->3->6->5->8->7->10->9

  std::vector<ListNode> input_nodes{
      ListNode{1}, ListNode{2}, ListNode{3}, ListNode{4}, ListNode{5},
      ListNode{6}, ListNode{7}, ListNode{8}, ListNode{9}, ListNode{10}};

  for (size_t i{}; i < input_nodes.size() - 1; i++)
    input_nodes[i].next = &input_nodes[i + 1];

  ListNode* input{&input_nodes[0]};

  while (input) {
    std::cout << input->val;
    input = input->next;
    if (input)
      std::cout << " -> ";
    else
      std::cout << '\n';
  }

  const int k = 2;

  Solution s{};

  ListNode* head = s.reverseKGroup(&input_nodes[0], k);

  while (head) {
    std::cout << head->val;
    head = head->next;
    if (head)
      std::cout << " -> ";
    else
      std::cout << '\n';
  }

  std::cout << '\n';

  return 0;
}
