/*
You are given two non-empty linked lists representing two non-negative integers.
The digits are stored in reverse order and each of their nodes contain a single
digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the
number 0 itself.

Example

Input:  (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.
*/

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode* next;
  ListNode(const int x) : val{x}, next{} {}
};

#include <iostream>

using namespace std;

static int sres = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

class Solution {
 public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    if (!l1)
      return l2;
    if (!l2)
      return l1;

    int carry{};
    ListNode* head{l1};

    while (true) {
      l1->val += l2->val + carry;
      carry = l1->val > 9 ? 1 : 0;
      l1->val %= 10;
      if (nullptr == l1->next && nullptr != l2->next)
        l1->next = new ListNode{0};
      else if (nullptr != l1->next && nullptr == l2->next)
        l2->next = new ListNode{0};
      else if (nullptr == l1->next && nullptr == l2->next) {
        if (carry)
          l1->next = new ListNode{1};
        break;
      }

      l1 = l1->next;
      l2 = l2->next;
    }

    return head;
  }
};

int main() {
  Solution s{};

  ListNode n1{2};
  ListNode n2{4};
  ListNode n3{3};
  ListNode n4{5};
  ListNode n5{6};
  ListNode n6{4};

  n1.next = &n2;
  n2.next = &n3;

  n4.next = &n5;
  n5.next = &n6;

  const ListNode* sum{s.addTwoNumbers(&n1, &n4)};

  cout << "s.addTwoNumbers({2 -> 4 -> 3 -> nullptr}, {5 -> 6 -> 4 -> nullptr}) "
          "-> {";

  while (sum) {
    cout << sum->val << " -> ";
    sum = sum->next;
  }

  cout << "nullptr}\n";

  return 0;
}
