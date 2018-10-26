/*
138. Copy list with random pointer (difficult level: medium)

A linked list is given such that each node contains an additional random pointer
which could point to any node in the list or null.

Return a deep copy of the list.
*/

#include <algorithm>
#include <chrono>
#include <iostream>
#include <queue>
#include <random>
#include <unordered_map>
#include <vector>

using namespace std;

// Definition for singly-linked list with a random pointer.
struct RandomListNode {
  int label;
  RandomListNode *next, *random;
  RandomListNode(const int x = 0) : label{x}, next{}, random{} {}

  RandomListNode& operator++() {
    ++label;
    return *this;
  }
};

class Solution {
  unordered_map<RandomListNode*, RandomListNode*> already_cloned_nodes_;

 public:
  Solution() { Solution::start_stop_timer(true); }
  ~Solution() {
    for (const auto& p : already_cloned_nodes_)
      delete p.second;
    already_cloned_nodes_.clear();
    cout << "\nElapsed time: " << Solution::start_stop_timer() << " seconds\n";
  }

  RandomListNode* copyRandomList(RandomListNode* head) {
    if (!head)
      return nullptr;

    for (const auto& p : already_cloned_nodes_)
      delete p.second;

    already_cloned_nodes_.clear();

    RandomListNode* cloned_head{new RandomListNode{head->label}};
    already_cloned_nodes_.emplace(head, cloned_head);

    queue<pair<RandomListNode*, RandomListNode*>> q{
        {make_pair(head, cloned_head)}};

    while (!q.empty()) {
      RandomListNode* current_orig_node{q.front().first};
      RandomListNode* current_cloned_node{q.front().second};
      q.pop();

      if (current_orig_node->next) {
        if (already_cloned_nodes_.find(current_orig_node->next) ==
            end(already_cloned_nodes_)) {
          RandomListNode* cloned_current_next_node{
              new RandomListNode{current_orig_node->next->label}};
          already_cloned_nodes_.emplace(current_orig_node->next,
                                        cloned_current_next_node);
          current_cloned_node->next = cloned_current_next_node;
          q.emplace(current_orig_node->next, cloned_current_next_node);
        } else
          current_cloned_node->next =
              already_cloned_nodes_.at(current_orig_node->next);
      }

      if (current_orig_node->random) {
        if (already_cloned_nodes_.find(current_orig_node->random) ==
            end(already_cloned_nodes_)) {
          RandomListNode* cloned_current_random_node{
              new RandomListNode{current_orig_node->random->label}};
          already_cloned_nodes_.emplace(current_orig_node->random,
                                        cloned_current_random_node);
          current_cloned_node->random = cloned_current_random_node;
          q.emplace(current_orig_node->random, cloned_current_random_node);
        } else
          current_cloned_node->random =
              already_cloned_nodes_.at(current_orig_node->random);
      }
    }

    return already_cloned_nodes_.at(head);
  }

  friend ostream& operator<<(ostream&, const RandomListNode*);

  static double start_stop_timer(const bool is_start_timer = false) {
    static chrono::high_resolution_clock::time_point start_time;
    if (is_start_timer)
      start_time = chrono::high_resolution_clock::now();

    return chrono::duration_cast<chrono::duration<double>>(
               chrono::high_resolution_clock::now() - start_time)
        .count();
  }
};

ostream& operator<<(ostream& os, const RandomListNode* node) {
  os << '[';
  while (node) {
    cout << node->label;
    if (node->next)
      os << " -> ";
    node = node->next;
  }
  os << ']';

  return os;
}

int main() {
  Solution s{};

  // random_device rd{};
  mt19937 random_engine{static_cast<unsigned>(
      chrono::system_clock::now().time_since_epoch().count())};
  uniform_int_distribution<size_t> min_max_size{10u, 100u};

  const size_t random_values_size{min_max_size(random_engine)};

  vector<RandomListNode> random_values(random_values_size);
  iota(begin(random_values), end(random_values), RandomListNode{1});
  random_shuffle(begin(random_values), end(random_values));

  for (size_t i{}; i < random_values_size - 1; ++i)
    random_values[i].next = &random_values[i + 1];

  uniform_int_distribution<size_t> min_max_random_pointers{1u, random_values_size};

  const size_t min_max_random_pointers_size{
      min_max_random_pointers(random_engine)};

  for (size_t i{}; i < min_max_random_pointers_size; ++i)
    random_values[min_max_random_pointers(random_engine) - 1].random =
        &random_values[min_max_random_pointers(random_engine) - 1];

  RandomListNode* cloned_linked_list_head{s.copyRandomList(&random_values[0])};

  cout << cloned_linked_list_head << '\n';
}
