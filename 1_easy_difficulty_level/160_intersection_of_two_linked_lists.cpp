/*
Write a program to find the node at which the intersection of two singly linked
lists begins.

For example, the following two linked lists:

A:          a1 → a2
                   ↘
                     c1 → c2 → c3
                   ↗
B:     b1 → b2 → b3

begin to intersect at node c1.

Notes:

    If the two linked lists have no intersection at all, return null.
    The linked lists must retain their original structure after the function
returns. You may assume there are no cycles anywhere in the entire linked
structure. Your code should preferably run in O(n) time and use only O(1)
memory.

Credits:
Special thanks to @stellari for adding this problem and creating all test cases.
*/

#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode* next;

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
  ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    if (!headA || !headB)
      return nullptr;

    unordered_set<ListNode*> visited_nodes_1{};
    unordered_set<ListNode*> visited_nodes_2{};

    while (headA || headB) {
      if (headA) {
        visited_nodes_1.insert(headA);
        if (visited_nodes_2.count(headA))
          return headA;
        headA = headA->next;
      }

      if (headB) {
        visited_nodes_2.insert(headB);
        if (visited_nodes_1.count(headB))
          return headB;
        headB = headB->next;
      }
    }

    return nullptr;
  }
};

int main() {
  Solution s{};

  vector<ListNode> list1{ListNode{1}, ListNode{2}, ListNode{3}, ListNode{3},
                         ListNode{4}, ListNode{4}, ListNode{5}};
  for (size_t i{}; i < list1.size() - 1; i++)
    list1[i].next = &list1[i + 1];
  vector<ListNode> list2{ListNode{1}, ListNode{1}, ListNode{1}, ListNode{2},
                         ListNode{3}};
  for (size_t i{}; i < list2.size() - 1; i++)
    list2[i].next = &list2[i + 1];
  vector<ListNode> list3{ListNode{8}, ListNode{9}, ListNode{10}, ListNode{11},
                         ListNode{12}};

  for (size_t i{}; i < list3.size() - 1; i++)
    list3[i].next = &list3[i + 1];
  list1.back().next = &list3[0];
  list2.back().next = &list3[0];

  ListNode* intersection_node{s.getIntersectionNode(&list1[0], &list2[0])};

  cout << "s.getIntersectionNode({1->2->3->3->4->4->5->8->9->10->11->12}, "
          "{1->1->1->2->3->8->9->10->11->12}) -> ";
  pretty_print(intersection_node, cout);
  cout << '\n';

  return 0;
}
