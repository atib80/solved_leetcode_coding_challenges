/*
82. Leetcode coding challenge: Remove duplicates from sorted list II

Given a sorted linked list, delete all nodes that have duplicate numbers,
leaving only distinct numbers from the original list.

Example 1:

Input: 1->2->3->3->4->4->5
Output: 1->2->5

Example 2:

Input: 1->1->1->2->3
Output: 2->3
*/

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

static int sres = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode* next{};

  ListNode(const int x) : val{x}, next{} {}
};

ostream& pretty_print(const ListNode* list, ostream& os) {
  os << '[';
  while (list) {
    os << list->val << "->";
    list = list->next;
  }
  os << "nullptr]";
  return os;
}

class Solution {
 public:
  ListNode* deleteDuplicates(ListNode* head) {
    if (!head || nullptr == head->next)
      return head;

    ListNode *prev{head}, *next{head->next}, *current{}, *start{};
    int value{head->val};

    while (true) {
      while (value == next->val) {
        next = next->next;
        if (!next)
          break;
      }

      if (prev->next == next) {
        if (!start) {
          start = prev;
          current = start;
        } else {
          current->next = prev;
          current = current->next;
        }
      }

      value = next->val;
      prev = next;
      next = next->next;

      if (!next) {
        current->next = prev;
        break;
      }
    }

    return start;
  }
};

int main() {
  Solution s{};

  vector<ListNode> list{ListNode{1}, ListNode{2}, ListNode{3}, ListNode{3},
                        ListNode{4}, ListNode{4}, ListNode{5}};
  for (size_t i{}; i < list.size() - 1; i++)
    list[i].next = &list[i + 1];
  ListNode* head{s.deleteDuplicates(&list[0])};
  cout << "s.deleteDuplicates({ 1, 2, 3, 3, 4, 4, 5 }) -> ";
  pretty_print(head, cout);  // expected output: 1->2->5
  cout << '\n';
  vector<ListNode> list2{ListNode{1}, ListNode{1}, ListNode{1}, ListNode{2},
                         ListNode{3}};
  for (size_t i{}; i < list2.size() - 1; i++)
    list2[i].next = &list2[i + 1];
  head = s.deleteDuplicates(&list2[0]);
  cout << "s.deleteDuplicates({ 1->1->1->2->3 }) -> ";
  pretty_print(head, cout);  // expected output: 2->3
  cout << '\n';

  return 0;
}
