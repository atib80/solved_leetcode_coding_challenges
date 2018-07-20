/*
86. Leetcode coding challenge: Partition list

Given a linked list and a value x, partition it such that all nodes less than x
come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two
partitions.

Example:

Input:  head = 1->4->3->2->5->2, x = 3
Output: 1->2->2->4->3->5
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
  ListNode* partition(ListNode* head, const int x) {
    if (!head || nullptr == head->next)
      return head;

    ListNode *new_head{}, *start{}, *current{head},
        *greater_equal_nodes_start{}, *greater_equal_nodes{};

    while (current) {
      if (current->val >= x) {
        ListNode* next = current->next;
        current->next = nullptr;
        if (!greater_equal_nodes_start)
          greater_equal_nodes_start = greater_equal_nodes = current;
        else {
          greater_equal_nodes->next = current;
          greater_equal_nodes = greater_equal_nodes->next;
        }

        current = next;
        continue;

      } else {
        if (!start) {
          new_head = current;
          start = new_head;
        } else {
          start->next = current;
          start = start->next;
        }
      }

      current = current->next;
    }

    if (!start)
      return greater_equal_nodes_start;

    start->next = greater_equal_nodes_start;

    return new_head;
  }
};

int main() {
  Solution s{};

  vector<ListNode> list{ListNode{1}, ListNode{4}, ListNode{3},
                        ListNode{2}, ListNode{5}, ListNode{2}};
  for (size_t i{}; i < list.size() - 1; i++)
    list[i].next = &list[i + 1];
  ListNode* head{s.partition(&list[0], 3)};
  cout << "s.partition({ 1, 4, 3, 2, 5, 2 }, 3) -> ";
  pretty_print(head, cout);  // expected output: 1->2->2->4->3->5->nullptr
  cout << '\n';

  list.assign({ListNode{1}, ListNode{1}});
  for (size_t i{}; i < list.size() - 1; i++)
    list[i].next = &list[i + 1];
  head = s.partition(&list[0], 0);
  cout << "s.partition({ 1, 1 }, 0) -> ";
  pretty_print(head, cout);  // expected output: nullptr
  cout << '\n';

  return 0;
}
