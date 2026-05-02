#include <bits/stdc++.h>
using namespace std;

struct Trie {
  void insert(const string& word) {
    int curr = 0;
    for (const char c : word) {
      const int idx = nodes[curr].child(c);
      if (idx == -1) {
        nodes[curr].child(c) = nodes.size();
        nodes.emplace_back(TrieNode());
      }
      curr = nodes[curr].child(c);
    }
    nodes[curr].is_word = true;
  }

  generator<int> find_matches(const string_view s) const {
    int curr = 0;
    int len = 0;

    for (const char c : s) {
      curr = nodes[curr].child(c);
      if (curr == -1) break;
      len++;
      if (nodes[curr].is_word) co_yield len;
    }
  }

 private:
  struct TrieNode {
    bool is_word = false;
    int& child(const char c) { return children[c - 'a']; }
    int child(const char c) const { return children[c - 'a']; }
    TrieNode() { children.fill(-1); }

   private:
    array<int, 26> children;
  };

  vector<TrieNode> nodes{TrieNode()};
};

class Solution {
  string s;
  Trie trie;
  int memo[57];

  int dp(const size_t idx) {
    if (idx == s.size()) return 0;
    if (~memo[idx]) return memo[idx];

    int res = dp(idx + 1);

    for (const int len : trie.find_matches(string_view(s).substr(idx))) {
      res = max(res, len + dp(idx + len));
    }

    return memo[idx] = res;
  }

 public:
  int minExtraChar(const string input, const vector<string>& dictionary) {
    memset(memo, -1, sizeof memo);
    this->s = input;
    for (const string& w : dictionary) {
      trie.insert(w);
    }

    return s.size() - dp(0);
  }
};
