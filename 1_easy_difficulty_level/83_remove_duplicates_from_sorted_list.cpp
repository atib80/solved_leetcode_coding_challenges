/*
83. Leetcode coding challenge: Remove duplicates from sorted list

Given a sorted linked list, delete all duplicates such that each element appear
only once.

Example 1:

Input:  1->1->2
Output: 1->2

Example 2:

Input:  1->1->2->3->3
Output: 1->2->3
*/

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename... Args>
void unused(Args&&...) {}

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

    ListNode *next{head->next}, *current{head};
    int value{head->val};

    while (true) {
      while (value == next->val) {
        next = next->next;
        if (!next) {
          current->next = nullptr;
          return head;
        }
      }

      current->next = next;
      current = current->next;
      value = next->val;
      next = next->next;

      if (!next)
        return head;
    }
  }
};

int main(int argc, char** argv) {
  unused(argc, argv);

  Solution s{};

  vector<ListNode> list{ListNode{1}, ListNode{2}, ListNode{3}, ListNode{3},
                        ListNode{4}, ListNode{4}, ListNode{5}};
  for (size_t i{}; i < list.size() - 1; i++)
    list[i].next = &list[i + 1];
  ListNode* head{s.deleteDuplicates(&list[0])};
  cout << "s.deleteDuplicates({ 1, 2, 3, 3, 4, 4, 5 }) -> ";
  pretty_print(head, cout);  // expected output: 1->2->3->4->5->nullptr
  cout << '\n';
  vector<ListNode> list2{ListNode{1}, ListNode{1}, ListNode{1}, ListNode{2},
                         ListNode{3}};
  for (size_t i{}; i < list2.size() - 1; i++)
    list2[i].next = &list2[i + 1];
  head = s.deleteDuplicates(&list2[0]);
  cout << "s.deleteDuplicates({ 1->1->1->2->3 }) -> ";
  pretty_print(head, cout);  // expected output: 1->2->3->nullptr
  cout << '\n';

  vector<ListNode> list3{ListNode{1}, ListNode{1}, ListNode{2}};
  for (size_t i{}; i < list3.size() - 1; i++)
    list3[i].next = &list3[i + 1];
  head = s.deleteDuplicates(&list3[0]);
  cout << "s.deleteDuplicates({ 1->1->2 }) -> ";
  pretty_print(head, cout);  // expected output: 1->2->nullptr
  cout << '\n';

  vector<ListNode> list4{ListNode{1}, ListNode{2}, ListNode{2}};
  for (size_t i{}; i < list4.size() - 1; i++)
    list4[i].next = &list4[i + 1];
  head = s.deleteDuplicates(&list4[0]);
  cout << "s.deleteDuplicates({ 1->2->2 }) -> ";
  pretty_print(head, cout);  // expected output: 1->2->nullptr
  cout << '\n';

  vector<ListNode> list5{ListNode{1}, ListNode{1}, ListNode{2}, ListNode{3},
                         ListNode{3}};
  for (size_t i{}; i < list5.size() - 1; i++)
    list5[i].next = &list5[i + 1];
  head = s.deleteDuplicates(&list5[0]);
  cout << "s.deleteDuplicates({ 1->1->2->3->3 }) -> ";
  pretty_print(head, cout);  // expected output: 1->2->3->nullptr
  cout << '\n';

  return 0;
}