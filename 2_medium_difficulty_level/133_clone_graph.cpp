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
#include <iostream>
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

// Definition for undirected graph.
struct UndirectedGraphNode {
  int label;
  bool is_printed{};
  bool is_deleted{};
  vector<UndirectedGraphNode*> neighbors;

  UndirectedGraphNode(const int x) : label{x} {}

  UndirectedGraphNode(const UndirectedGraphNode& rhs)
      : label{rhs.label},
        is_printed{rhs.is_printed},
        is_deleted{rhs.is_deleted} {
    clone_graph(rhs);
  }

  UndirectedGraphNode& operator=(const UndirectedGraphNode& rhs) {
    if (this == &rhs)
      return *this;

    UndirectedGraphNode temp_obj{rhs};
    swap(temp_obj);
    return *this;
  }

  UndirectedGraphNode& operator=(UndirectedGraphNode&& rhs) noexcept {
    if (this == &rhs)
      return *this;

    label = rhs.label;
    rhs.label = -1;
    is_printed = rhs.is_printed;
    rhs.is_printed = true;
    is_deleted = rhs.is_deleted;
    rhs.is_deleted = true;
    neighbors = move(rhs.neighbors);
    return *this;
  }

  void swap(UndirectedGraphNode& rhs) noexcept {
    using std::swap;

    swap(label, rhs.label);
    swap(is_printed, rhs.is_printed);
    swap(is_deleted, rhs.is_deleted);
    neighbors.swap(rhs.neighbors);
  }

  UndirectedGraphNode(UndirectedGraphNode&& rhs) noexcept
      : label{rhs.label},
        is_printed{rhs.is_printed},
        is_deleted{rhs.is_deleted},
        neighbors{move(rhs.neighbors)} {
    rhs.label = -1;
    rhs.is_printed = true;
    rhs.is_deleted = true;
  }

  ~UndirectedGraphNode() {
    is_deleted = true;
    for (UndirectedGraphNode* n : neighbors) {
      if (this == n || n->is_deleted)
        continue;
      delete n;
    }
  }

  bool get_is_printed() const { return is_printed; }

  void set_is_printed(const bool is_printed_val) {
    for (UndirectedGraphNode* node : neighbors) {
      if (this != node)
        node->set_is_printed(is_printed_val);
    }
    is_printed = is_printed_val;
  }

 private:
  void clone_graph(const UndirectedGraphNode& src) {
    unordered_map<int, UndirectedGraphNode*> graph_nodes{};
    unordered_set<int> already_visited_graph_nodes{};

    for (UndirectedGraphNode* node : src.neighbors) {
      UndirectedGraphNode* gn;

      if (graph_nodes.find(node->label) == end(graph_nodes)) {
        gn = new UndirectedGraphNode{node->label};
        graph_nodes.emplace(node->label, gn);
      } else
        gn = graph_nodes.at(node->label);

      neighbors.emplace_back(gn);

      queue<UndirectedGraphNode*> q{{node}};

      while (!q.empty()) {
        UndirectedGraphNode* current_node{q.front()};
        q.pop();

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
    }
  }
};

void swap(UndirectedGraphNode& lhs, UndirectedGraphNode& rhs) noexcept {
  lhs.swap(rhs);
}

ostream& operator<<(ostream& os, UndirectedGraphNode& gn) {
  gn.is_printed = true;
  os << "Node: " << gn.label << " is connected to nodes (";
  if (!gn.neighbors.empty()) {
    for (size_t i{}; i < gn.neighbors.size() - 1; ++i)
      os << gn.neighbors[i]->label << ',';
    os << gn.neighbors.back()->label << ")\n";
    for (UndirectedGraphNode* n : gn.neighbors) {
      if (n->label != gn.label && !n->is_printed)
        os << *n;
    }
  }

  return os;
}

class Solution {
 public:
  UndirectedGraphNode* cloneGraph(UndirectedGraphNode* node) {
    if (!node)
      return nullptr;

    unordered_map<int, UndirectedGraphNode*> graph_nodes{};
    unordered_set<int> already_visited_graph_nodes{};
    queue<UndirectedGraphNode*> q{{node}};

    while (!q.empty()) {
      UndirectedGraphNode* current_node{q.front()};
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
};

int main() {
  Solution s{};

  UndirectedGraphNode head_node{0}, node1{1}, node2{2};
  head_node.neighbors.emplace_back(&node1);
  head_node.neighbors.emplace_back(&node2);
  node1.neighbors.emplace_back(&node2);
  node2.neighbors.emplace_back(&node2);

  cout << "Original graph's nodes:\n" << head_node << '\n';

  head_node.set_is_printed(false);

  const unique_ptr<UndirectedGraphNode> cloned_graph{s.cloneGraph(&head_node)};
  if (cloned_graph)
    cout << *cloned_graph;

  return 0;
}
