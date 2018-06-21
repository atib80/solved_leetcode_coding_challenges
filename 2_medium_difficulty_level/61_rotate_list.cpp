/*
61. leetcode coding challenge: Rotate List

Given a linked list, rotate the list to the right by k places, where k is
non-negative.

Example 1:

Input: 1->2->3->4->5->NULL, k = 2
Output: 4->5->1->2->3->NULL
Explanation:
rotate 1 steps to the right: 5->1->2->3->4->NULL
rotate 2 steps to the right: 4->5->1->2->3->NULL

Example 2:

Input: 0->1->2->NULL, k = 4
Output: 2->0->1->NULL
Explanation:
rotate 1 steps to the right: 2->0->1->NULL
rotate 2 steps to the right: 1->2->0->NULL
rotate 3 steps to the right: 0->1->2->NULL
rotate 4 steps to the right: 2->0->1->NULL
*/

#include <stl_helper_functions.h>
#include <iostream>
#include <vector>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode* next;
  explicit ListNode(const int x) : val{x}, next{} {}
};

static int sres = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

class Solution {
 public:
  ListNode* rotateRight(ListNode* head, int k) {
    if (!head)
      return nullptr;

    if (!k)
      return head;

    ListNode* last{head};
    int slist_size{1};

    ListNode* prev{last};

    while (last->next) {
      prev = last;
      last = last->next;
      slist_size++;
    }

    if (1 == slist_size)
      return head;

    if (1 == k) {
      last->next = head;
      head = last;
      prev->next = nullptr;
      return head;
    }

    if (k >= slist_size) {
      k %= slist_size;
      if (!k)
        return head;
    }

    ListNode* next{head};
    last->next = head;

    for (int i{}; i < slist_size - k; i++) {
      prev = next;
      next = next->next;
    }

    head = next;
    prev->next = nullptr;
    return head;
  }
};

int main() {
  experimental::unused_args(sres);
  Solution s{};
  vector<ListNode> l1{ListNode{1}, ListNode{2}, ListNode{3}, ListNode{4},
                      ListNode{5}};
  for (size_t i{}; i < l1.size() - 1; i++)
    l1[i].next = &l1[i + 1];
  ListNode* head{s.rotateRight(
      &l1[0], 2)};  // expected output: [4 -> 5 -> 1 -> 2 -> 3 -> NULL]
  cout << "s.rotateRight([1 -> 2 -> 3 -> 4 -> 5 -> NULL], 2) -> [";
  ListNode* current{head};
  while (current) {
    cout << current->val << " -> ";
    current = current->next;
  }
  cout << "NULL]\n";

  vector<ListNode> l2{ListNode{0}, ListNode{1}, ListNode{2}};
  for (size_t i{}; i < l2.size() - 1; i++)
    l2[i].next = &l2[i + 1];
  head = s.rotateRight(&l2[0], 4);  // expected output: [2 -> 0 -> 1 -> NULL]
  cout << "s.rotateRight([0 -> 1 -> 2 -> NULL], 4) -> [";
  current = head;
  while (current) {
    cout << current->val << " -> ";
    current = current->next;
  }
  cout << "NULL]\n";

  vector<ListNode> l3{ListNode{1}, ListNode{2}};
  for (size_t i{}; i < l3.size() - 1; i++)
    l3[i].next = &l3[i + 1];
  head = s.rotateRight(&l3[0], 0);  // expected output: [1 -> 2 -> NULL]
  cout << "s.rotateRight([1 -> 2 -> NULL], 0) -> [";
  current = head;
  while (current) {
    cout << current->val << " -> ";
    current = current->next;
  }
  cout << "NULL]\n";

  vector<ListNode> l4{ListNode{1}, ListNode{2}};
  for (size_t i{}; i < l4.size() - 1; i++)
    l4[i].next = &l4[i + 1];
  head = s.rotateRight(&l4[0], 1);  // expected output: [2 -> 1 -> NULL]
  cout << "s.rotateRight([1 -> 2 -> NULL], 1) -> [";
  current = head;
  while (current) {
    cout << current->val << " -> ";
    current = current->next;
  }
  cout << "NULL]\n";

  vector<ListNode> l5{ListNode{1}, ListNode{2}, ListNode{3}};
  for (size_t i{}; i < l5.size() - 1; i++)
    l5[i].next = &l5[i + 1];
  head = s.rotateRight(&l5[0],
                       2000000000);  // expected output: [2 -> 3 -> 1 -> NULL]
  cout << "s.rotateRight([1 -> 2 -> 3 -> NULL], 2000000000) -> [";
  current = head;
  while (current) {
    cout << current->val << " -> ";
    current = current->next;
  }
  cout << "NULL]\n";

  vector<ListNode> l6{ListNode{1}, ListNode{2}, ListNode{3}, ListNode{4},
                      ListNode{5}};
  for (size_t i{}; i < l6.size() - 1; i++)
    l6[i].next = &l6[i + 1];
  head = s.rotateRight(&l6[0],
                       1);  // expected output: [5 -> 1 -> 2 -> 3 -> 4 -> NULL]
  cout << "s.rotateRight([1 -> 2 -> 3 -> 4 -> 5 -> NULL], 1) -> [";
  current = head;
  while (current) {
    cout << current->val << " -> ";
    current = current->next;
  }
  cout << "NULL]\n";

  return 0;
}
