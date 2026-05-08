#include <bits/stdc++.h>
using namespace std;

struct Trie {
  void insert(const string& s, const int val) {
    int curr = 0;
    const int prev_val = curr_val[s];
    curr_val[s] = val;

    for (const char c : s) {
      if (nodes[curr].edges[c - 'a'] == -1) {
        nodes[curr].edges[c - 'a'] = nodes.size();
        nodes.emplace_back(Node());
      }

      curr = nodes[curr].edges[c - 'a'];
      nodes[curr].val += val - prev_val;
    }
  }

  int query(const string& s) const {
    int curr = 0;

    for (const char c : s) {
      if (nodes[curr].edges[c - 'a'] == -1) return 0;
      curr = nodes[curr].edges[c - 'a'];
    }

    return nodes[curr].val;
  }

 private:
  unordered_map<string, int> curr_val;
  struct Node {
    array<int, 26> edges;
    int val;
    Node() : val(0) { edges.fill(-1); }
  };

  vector<Node> nodes{Node()};
};

class MapSum {
  Trie trie;

 public:
  void insert(const string key, const int val) { trie.insert(key, val); }
  int sum(const string prefix) { return trie.query(prefix); }
};
