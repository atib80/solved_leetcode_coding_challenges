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

#include <algorithm>
#include <iostream>
#include <string>

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
    if (0 == l1->val)
      return l2;
    if (0 == l2->val)
      return l1;

    string first_number{}, second_number{};
    first_number.reserve(64);
    second_number.reserve(64);
    while (l1) {
      first_number.push_back(l1->val % 10 + '0');
      l1 = l1->next;
    }

    while (l2) {
      second_number.push_back(l2->val % 10 + '0');
      l2 = l2->next;
    }

    const size_t first_number_len{first_number.length()};
    const size_t second_number_len{second_number.length()};

    if (first_number_len < second_number_len) {
      first_number.resize(second_number_len, '0');

    } else if (first_number_len > second_number_len) {
      second_number.resize(first_number_len, '0');
    }

    string result(max(first_number_len, second_number_len) + 1, '0');

    size_t carry{};
    for (size_t i{}; i < first_number.length(); i++) {
      const size_t sum{(first_number[i] - '0') + (second_number[i] - '0') +
                       carry};
      if (sum > 9)
        carry = 1;
      else
        carry = 0;
      result[i] = sum % 10 + '0';
    }

    if (carry)
      result.back() = '1';
    else
      result.erase(--end(result));

    ListNode* result_fll = new ListNode{result[0] - '0'};

    ListNode* head{result_fll};

    for (size_t i{1}; i < result.length(); i++) {
      result_fll->next = new ListNode{result[i] - '0'};
      result_fll = result_fll->next;
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
