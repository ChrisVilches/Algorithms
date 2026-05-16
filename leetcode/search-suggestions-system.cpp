#include <bits/stdc++.h>
using namespace std;

struct Trie {
  void insert(const string& s, const int idx) {
    int curr = 0;

    for (const char c : s) {
      if (nodes[curr].edges[c - 'a'] == -1) {
        nodes[curr].edges[c - 'a'] = nodes.size();
        nodes.emplace_back(Node());
      }

      curr = nodes[curr].edges[c - 'a'];
    }

    nodes[curr].word_idx = idx;
  }

  int next_node(const int node_idx, const char c) const {
    return nodes[node_idx].edges[c - 'a'];
  }

  vector<int> query(const int node_idx) const {
    vector<int> res;

    const function<void(int)> dfs = [&](const int u) {
      if (u == -1) return;
      if (res.size() == 3) return;
      if (nodes[u].word_idx != -1) res.emplace_back(nodes[u].word_idx);
      for (const int v : nodes[u].edges) dfs(v);
    };

    dfs(node_idx);

    return res;
  }

 private:
  struct Node {
    array<int, 26> edges;
    int word_idx;
    Node() : word_idx(-1) { edges.fill(-1); }
  };

  vector<Node> nodes{Node()};
};

class Solution {
 public:
  vector<vector<string>> suggestedProducts(const vector<string>& products,
                                           const string search) {
    Trie trie;
    for (size_t i = 0; i < products.size(); i++) {
      trie.insert(products[i], i);
    }

    vector<vector<string>> ans;

    int curr_node = 0;

    for (const char c : search) {
      if (curr_node != -1) {
        curr_node = trie.next_node(curr_node, c);
      }

      ans.push_back({});
      for (const int i : trie.query(curr_node)) {
        ans.back().emplace_back(products[i]);
      }
    }

    return ans;
  }
};
