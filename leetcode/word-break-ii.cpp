#include <bits/stdc++.h>
using namespace std;

struct RadixTree {
  struct Edge {
    string_view seq;
    int node_idx = -1;
  };

  struct Node {
    int word_idx;
    array<Edge, 26> edges;
    Node(const int i = -1) : word_idx(i) {}
    inline bool has_edge(const char c) const { return edges[c - 'a'].node_idx != -1; }
  };

  struct Iterator {
    int get_word_idx() const { return e == 0 ? tree->nodes[node_idx].word_idx : -1; }

    bool next(const char c) {
      const Node& node = tree->nodes[node_idx];

      if (e == 0 && !node.has_edge(c)) return false;

      const char edge_char = e == 0 ? c : e;
      const size_t i = e == 0 ? 0 : idx;

      const Edge& edge = node.edges[edge_char - 'a'];

      if (edge.seq[i] != c) return false;

      if (i + 1 == edge.seq.size()) {
        this->node_idx = edge.node_idx;
        this->e = 0;
        this->idx = 0;
      } else {
        this->e = edge_char;
        this->idx++;
      }

      return true;
    }

    Iterator(const RadixTree* const t) : tree(t), node_idx(0), e(0), idx(0) {}

   private:
    const RadixTree* const tree;
    int node_idx;
    char e;
    size_t idx;
  };

  Iterator begin() const { return Iterator(this); }

  void insert(const string& s, const int idx) {
    int curr = 0;
    size_t i = 0;

    while (i < s.size() && nodes[curr].has_edge(s[i])) {
      const int curr_char = s[i] - 'a';
      const auto [seq, node] = nodes[curr].edges[curr_char];

      for (size_t k = 0; k < seq.size() && i < s.size(); k++, i++) {
        if (seq[k] == s[i]) {
          if (i + 1 == s.size() && k + 1 != seq.size()) {
            const int mid = add_node(idx);
            nodes[mid].edges[seq[k + 1] - 'a'] = {seq.substr(k + 1), node};
            nodes[curr].edges[curr_char] = {seq.substr(0, k + 1), mid};
            return;
          }
        } else {
          const int mid = add_node();
          nodes[mid].edges[s[i] - 'a'] = {string_view(s).substr(i), add_node(idx)};
          nodes[mid].edges[seq[k] - 'a'] = {seq.substr(k), node};
          nodes[curr].edges[curr_char] = {seq.substr(0, k), mid};
          return;
        }
      }

      curr = node;
    }

    if (i == s.size()) {
      nodes[curr].word_idx = idx;
    } else {
      nodes[curr].edges[s[i] - 'a'] = {string_view(s).substr(i), add_node(idx)};
    }
  }

 private:
  vector<Node> nodes{Node()};

  int add_node(const int idx = -1) {
    nodes.emplace_back(Node(idx));
    return static_cast<int>(nodes.size() - 1);
  }
};

class Solution {
 public:
  vector<string> wordBreak(const string s, const vector<string>& words) {
    RadixTree tree;
    for (size_t i = 0; i < words.size(); i++) {
      tree.insert(words[i], i);
    }

    vector<string_view> curr;
    vector<string> ans;

    const function<void(int)> recur = [&](const size_t idx) {
      if (idx == s.size()) {
        ans.emplace_back(views::join_with(curr, ' ') | ranges::to<string>());
        return;
      }

      RadixTree::Iterator it = tree.begin();

      for (size_t i = idx; i < s.size(); i++) {
        if (!it.next(s[i])) break;

        const int word_idx = it.get_word_idx();
        if (word_idx == -1) continue;

        curr.emplace_back(words[word_idx]);
        recur(i + 1);
        curr.pop_back();
      }
    };

    recur(0);

    return ans;
  }
};
