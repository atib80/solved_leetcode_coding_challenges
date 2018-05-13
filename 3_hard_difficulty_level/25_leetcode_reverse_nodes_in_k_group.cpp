/*
Leetcode coding challenge: Reverse nodes in k group

Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.
k is a positive integer and is less than or equal to the length of the linked list. 
If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

Example:

Given this linked list: 1->2->3->4->5
For k = 2, you should return: 2->1->4->3->5
For k = 3, you should return: 3->2->1->4->5

Note:
Only constant extra memory is allowed.
You may not alter the values in the list's nodes, only nodes itself may be changed.
*/

#include <iostream>
#include <stack>

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode* next;
  ListNode(const int x) : val{x}, next(nullptr) {}
};

class Solution {
 public:
  ListNode* reverseKGroup(ListNode* head, int k) {
    if (!head || nullptr == head->next) return head;
    k--;

    std::stack<ListNode*> s{};

    ListNode* updated_head{};
    ListNode* last{head};
    ListNode* prev_end{};

    while (true) {
      for (int i{}; i < k; i++) {
        if (!last) {
          if (!updated_head) return head;
          return updated_head;
        }
        s.emplace(last);
        last = last->next;
      }

      if (!last) {
        if (!updated_head) return head;
        return updated_head;
      }

      if (!updated_head) updated_head = last;

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
  ListNode l1{1};
  ListNode l2{2};
  ListNode l3{3};
  ListNode l4{4};
  ListNode l5{5};

  l1.next = &l2;
  l2.next = &l3;
  l3.next = &l4;
  l4.next = &l5;

  ListNode* input{&l1};

  while (input) {
    std::cout << input->val;
    input = input->next;
    if (input) std::cout << " -> ";
  }

  std::cout << '\n';

  const int k = 2;

  Solution s{};

  ListNode* head = s.reverseKGroup(&l1, k);

  while (head) {
    std::cout << head->val;
    head = head->next;
    if (head) std::cout << " -> ";
  }

  std::cout << '\n';

  return 0;
}
