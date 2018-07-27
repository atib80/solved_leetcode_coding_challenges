/*
141. Leetcode coding challenge: Linked list cycle

Given a linked list, determine if it has a cycle in it.

Follow up:
Can you solve it without using extra space?
*/

#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode* next;

  ListNode(const int x) : val{x}, next{} {}
};

class Solution {
 public:
  bool hasCycle(const ListNode* head) {
    const ListNode *prev{head}, *next{head};

    while (next && next->next && next->next->next) {
      prev = prev->next;
      next = next->next->next;
      if (next == prev)
        return true;
    }

    return false;
  }
};

int main() {
  Solution s{};

  vector<ListNode> list{ListNode{1}, ListNode{2}, ListNode{3}, ListNode{3},
                        ListNode{4}, ListNode{4}, ListNode{5}};
  for (size_t i{}; i < list.size() - 1; i++)
    list[i].next = &list[i + 1];
  list.back().next = &(list.front());
  cout << boolalpha << "s.hasCycle({ 1, 2, 3, 3, 4, 4, 5 }) -> "
       << s.hasCycle(&list[0]) << '\n';  // expected output: true

  vector<ListNode> list2{ListNode{1}, ListNode{1}, ListNode{1}, ListNode{2},
                         ListNode{3}};
  for (size_t i{}; i < list2.size() - 1; i++)
    list2[i].next = &list2[i + 1];
  cout << "s.hasCycle({ 1->1->1->2->3 }) -> " << s.hasCycle(&list2[0])
       << noboolalpha << '\n';  // expected output: false

  return 0;
}
