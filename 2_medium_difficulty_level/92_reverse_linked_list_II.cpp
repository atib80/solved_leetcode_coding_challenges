/*
92. Leetcode coding challenge: Reverse linked list II

Reverse a linked list from position m to n. Do it in one-pass.

Note: 1 ≤ m ≤ n ≤ length of list.

Example:

Input: 1->2->3->4->5->NULL, m = 2, n = 4
Output: 1->4->3->2->5->NULL
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
  ListNode* reverseBetween(ListNode* head, const int m, const int n) {
    if (!head || nullptr == head->next || m >= n)
      return head;

    ListNode *start{}, *current{head};

    int position{1};

    while (position < m) {
      start = current;
      current = current->next;
      if (!current)
        return head;
      position++;
    }

    ListNode *sub_list_start, *sub_list_end;
    sub_list_start = sub_list_end = current;
    current = current->next;
    ListNode* next{current};

    if (m + 1 == n) {
      sub_list_start->next = next->next;
      if (!start)
        head = next;
      else
        start->next = next;
      next->next = sub_list_start;
      return head;
    }

    for (int i{m + 1}; i <= n; i++) {
      ListNode* temp{current};
      current = current->next;
      next = current;
      temp->next = sub_list_start;
      sub_list_start = temp;
      if (!current)
        break;
    }

    sub_list_end->next = next;

    if (start) {
      start->next = sub_list_start;
      return head;
    } else
      return sub_list_start;
  }
};

int main() {
  Solution s{};

  vector<ListNode> list{ListNode{1}, ListNode{2}, ListNode{3}, ListNode{4},
                        ListNode{5}};
  for (size_t i{}; i < list.size() - 1; i++)
    list[i].next = &list[i + 1];
  ListNode* head{s.reverseBetween(&list[0], 2, 4)};
  cout << "s.reverseBetween({ 1, 2, 3, 4, 5, nullptr }, 2, 4) -> ";
  pretty_print(head, cout);  // expected output: 1->4->3->2->5->nullptr
  cout << '\n';

  list.assign({ListNode{1}, ListNode{2}, ListNode{3}});
  for (size_t i{}; i < list.size() - 1; i++)
    list[i].next = &list[i + 1];
  head = s.reverseBetween(&list[0], 2, 3);
  cout << "s.reverseBetween({ 1, 2, 3, nullptr }, 2, 3) -> ";
  pretty_print(head, cout);  // expected output: 1->3->2->nullptr
  cout << '\n';

  list.assign({ListNode{1}, ListNode{2}});
  for (size_t i{}; i < list.size() - 1; i++)
    list[i].next = &list[i + 1];
  head = s.reverseBetween(&list[0], 1, 2);
  cout << "s.reverseBetween({ 1, 2, nullptr }, 1, 2) -> ";
  pretty_print(head, cout);  // expected output: 2->1->nullptr
  cout << '\n';

  list.assign({ListNode{1}});
  for (size_t i{}; i < list.size() - 1; i++)
    list[i].next = &list[i + 1];
  head = s.reverseBetween(&list[0], 1, 1);
  cout << "s.reverseBetween({ 1, nullptr }, 1, 1) -> ";
  pretty_print(head, cout);  // expected output: 1->nullptr
  cout << '\n';

  list.assign({ListNode{1}, ListNode{2}, ListNode{3}});
  for (size_t i{}; i < list.size() - 1; i++)
    list[i].next = &list[i + 1];
  head = s.reverseBetween(&list[0], 1, 3);
  cout << "s.reverseBetween({ 1, 2, 3, nullptr }, 1, 3) -> ";
  pretty_print(head, cout);  // expected output: 3->2->1->nullptr
  cout << '\n';

  list.assign({ListNode{1}, ListNode{2}, ListNode{3}});
  for (size_t i{}; i < list.size() - 1; i++)
    list[i].next = &list[i + 1];
  head = s.reverseBetween(&list[0], 1, 2);
  cout << "s.reverseBetween({ 1, 2, 3, nullptr }, 1, 2) -> ";
  pretty_print(head, cout);  // expected output: 2->1->3->nullptr
  cout << '\n';

  return 0;
}
