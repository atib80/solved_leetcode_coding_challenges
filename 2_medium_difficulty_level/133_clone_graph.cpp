/*
133. Clone graph (difficulty level: medium)

Given the head of a graph, return a deep copy (clone) of the graph. Each node in
the graph contains a label (int) and a list (List[UndirectedGraphNode]) of its
neighbors. There is an edge between the given node and each of the nodes in its
neighbors.

OJ's undirected graph serialization (so you can understand error output):

Nodes are labeled uniquely.
We use # as a separator for each node, and , as a separator for node label and
each neighbor of the node.


As an example, consider the serialized graph {0,1,2#1,2#2,2}.

The graph has a total of three nodes, and therefore contains three parts as
separated by #.

    First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
    Second node is labeled as 1. Connect node 1 to node 2.
    Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming
a self-cycle.



Visually, the graph looks like the following:

       1
      / \
     /   \
    0 --- 2
         / \
         \_/

Note: The information about the tree serialization is only meant so that you can
understand error output if you get a wrong answer. You don't need to understand
the serialization to solve the problem.
*/

#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

// Definition for undirected graph.
struct UndirectedGraphNode {
  int label;
  vector<UndirectedGraphNode*> neighbors;

  UndirectedGraphNode(const int x = -1) : label{x} {}
};

class graph {
  const UndirectedGraphNode* head_node_;
  set<int> sorted_graph_indices_;
  unordered_map<int, unique_ptr<UndirectedGraphNode>> graph_nodes_;

  void clone_graph(const UndirectedGraphNode& src) {
    const int head_node_index{src.label};
    queue<const UndirectedGraphNode*> q{{&src}};
    unordered_set<int> already_visited_graph_nodes{head_node_index};

    while (!q.empty()) {
      const UndirectedGraphNode* current_node{q.front()};

      q.pop();

      if (graph_nodes_.find(current_node->label) == end(graph_nodes_)) {
        sorted_graph_indices_.emplace(current_node->label);
        graph_nodes_[current_node->label] =
            make_unique<UndirectedGraphNode>(current_node->label);
      }

      for (UndirectedGraphNode* gnode : current_node->neighbors) {
        if (graph_nodes_.find(gnode->label) == end(graph_nodes_)) {
          sorted_graph_indices_.emplace(gnode->label);
          graph_nodes_[gnode->label] =
              make_unique<UndirectedGraphNode>(gnode->label);
        }

        graph_nodes_.at(current_node->label)
            ->neighbors.emplace_back(graph_nodes_.at(gnode->label).get());

        if (already_visited_graph_nodes.find(gnode->label) ==
                end(already_visited_graph_nodes) &&
            graph_nodes_.at(current_node->label)->label != gnode->label) {
          already_visited_graph_nodes.emplace(gnode->label);
          q.emplace(gnode);
        }
      }
    }

    head_node_ = graph_nodes_.at(head_node_index).get();
  }

 public:
  graph(const UndirectedGraphNode* head_node = nullptr)
      : head_node_{head_node} {
    if (!head_node)
      return;

    clone_graph(*head_node_);
  }

  graph(const graph& rhs) : head_node_{} {
    if (rhs.head_node_) {
      const int head_node_index{rhs.head_node_->label};
      clone_graph(*rhs.head_node_);
      head_node_ = graph_nodes_.at(head_node_index).get();
    }
  }

  graph(graph&& rhs) noexcept
      : head_node_{rhs.head_node_},
        sorted_graph_indices_{move(rhs.sorted_graph_indices_)},
        graph_nodes_{move(rhs.graph_nodes_)} {}

  graph& operator=(const graph& rhs) {
    if (this == &rhs)
      return *this;

    graph temp_obj{rhs};
    swap(temp_obj);
    return *this;
  }

  graph& operator=(graph&& rhs) noexcept {
    if (this == &rhs)
      return *this;

    head_node_ = rhs.head_node_;
    sorted_graph_indices_ = move(rhs.sorted_graph_indices_);
    graph_nodes_ = move(rhs.graph_nodes_);

    return *this;
  }

  void swap(graph& rhs) noexcept {
    using std::swap;

    swap(head_node_, rhs.head_node_);
    sorted_graph_indices_.swap(rhs.sorted_graph_indices_);
    graph_nodes_.swap(rhs.graph_nodes_);
  }

  ~graph() = default;

  friend ostream& operator<<(ostream&, const graph&);

  explicit operator bool() const { return head_node_ != nullptr; }

  graph clone() const {
    graph temp_obj{*this};
    return temp_obj;
  }

  const UndirectedGraphNode* get_head_node() const { return head_node_; }

  int get_head_node_index() const {
    if (head_node_)
      return head_node_->label;
    return -1;
  }
};

void swap(graph& lhs, graph& rhs) noexcept {
  lhs.swap(rhs);
}

ostream& operator<<(ostream& os, const graph& g) {
  for (const int node_index : g.sorted_graph_indices_) {
    os << "Node: " << node_index << " is connected to nodes (";
    if (!g.graph_nodes_.at(node_index)->neighbors.empty()) {
      for (size_t i{}; i < g.graph_nodes_.at(node_index)->neighbors.size() - 1;
           ++i)
        os << g.graph_nodes_.at(node_index)->neighbors[i]->label << ',';
      os << g.graph_nodes_.at(node_index)->neighbors.back()->label;
    }

    os << ")\n";
  }

  return os;
}

class Solution {
 public:
  UndirectedGraphNode* cloneGraph(const UndirectedGraphNode* node) const {
    if (!node)
      return nullptr;

    unordered_map<int, UndirectedGraphNode*> graph_nodes{};
    unordered_set<int> already_visited_graph_nodes{node->label};
    queue<const UndirectedGraphNode*> q{{node}};

    while (!q.empty()) {
      const UndirectedGraphNode* current_node{q.front()};
      q.pop();

      UndirectedGraphNode* gn;

      if (graph_nodes.find(current_node->label) == end(graph_nodes)) {
        gn = new UndirectedGraphNode{current_node->label};
        graph_nodes.emplace(current_node->label, gn);
      } else
        gn = graph_nodes.at(current_node->label);

      for (const auto gnode : current_node->neighbors) {
        if (graph_nodes.find(gnode->label) == end(graph_nodes)) {
          const auto nn = new UndirectedGraphNode{gnode->label};
          graph_nodes.emplace(gnode->label, nn);
          gn->neighbors.emplace_back(nn);
        } else
          gn->neighbors.emplace_back(graph_nodes.at(gnode->label));

        if (already_visited_graph_nodes.find(gnode->label) ==
                end(already_visited_graph_nodes) &&
            gn->label != gnode->label) {
          already_visited_graph_nodes.emplace(gnode->label);
          q.emplace(gnode);
        }
      }
    }

    return graph_nodes.at(node->label);
  }

  static double start_stop_timer(const bool is_start_timer = false) {
    static chrono::high_resolution_clock::time_point start_time;
    if (is_start_timer)
      start_time = chrono::high_resolution_clock::now();

    return chrono::duration_cast<chrono::duration<double>>(
               chrono::high_resolution_clock::now() - start_time)
        .count();
  }
};

int main() {
  Solution s{};

  Solution::start_stop_timer(true);

  UndirectedGraphNode head_node{0}, node1{1}, node2{2};
  head_node.neighbors.emplace_back(&node1);
  head_node.neighbors.emplace_back(&node2);
  node1.neighbors.emplace_back(&node2);
  node2.neighbors.emplace_back(&node2);
  const graph graph_diagram{&head_node};

  cout << "Original graph's nodes:\n" << graph_diagram << '\n';

  // const graph cloned_graph_diagram{graph_diagram.clone()};
  const graph cloned_graph_diagram{s.cloneGraph(graph_diagram.get_head_node())};

  if (cloned_graph_diagram)
    cout << cloned_graph_diagram;

  cout << "Elapsed time: " << Solution::start_stop_timer() << " seconds\n";

  return 0;
}
