#include <bits/stdc++.h>
using namespace std;

struct Trie {
  void insert(const vector<string>& words, const int idx) {
    int curr = 0;
    update(words, curr, idx);

    for (const char c : views::reverse(words[idx])) {
      if (nodes[curr][c - 'a'] == -1) {
        nodes[curr][c - 'a'] = insert_node();
      }

      curr = nodes[curr][c - 'a'];
      update(words, curr, idx);
    }
  }

  int query(const string& s) const {
    int curr = 0;
    for (const char c : views::reverse(s)) {
      if (nodes[curr][c - 'a'] == -1) break;
      curr = nodes[curr][c - 'a'];
    }
    return best_word_idx[curr];
  }

  Trie() { insert_node(); }

 private:
  void update(const vector<string>& words, const int node, const int idx) {
    const int j = best_word_idx[node];

    if (j == -1) {
      best_word_idx[node] = idx;
      return;
    }

    const int a = words[idx].size();
    const int b = words[j].size();
    if (a < b || (a == b && idx < j)) {
      best_word_idx[node] = idx;
    }
  }

  int insert_node() {
    nodes.emplace_back();
    nodes.back().fill(-1);
    best_word_idx.emplace_back(-1);
    return nodes.size() - 1;
  }

  vector<array<int, 26>> nodes;
  vector<int> best_word_idx;
};

class Solution {
 public:
  vector<int> stringIndices(const vector<string>& words, const vector<string>& queries) {
    vector<int> ans;
    Trie trie;

    for (size_t i = 0; i < words.size(); i++) {
      trie.insert(words, i);
    }

    for (const string& s : queries) {
      ans.emplace_back(trie.query(s));
    }

    return ans;
  }
};
