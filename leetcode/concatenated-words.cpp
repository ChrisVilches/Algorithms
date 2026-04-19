#include <bits/stdc++.h>
using namespace std;

struct Trie {
  struct Node {
    array<int, 26> children;
    bool is_word = false;
    Node() { children.fill(-1); }
  };

  vector<Node> nodes{Node()};
  void insert(const string& s) {
    int curr = 0;
    for (const char c : s) {
      const int idx = c - 'a';
      if (nodes[curr].children[idx] == -1) {
        nodes[curr].children[idx] = nodes.size();
        nodes.emplace_back();
      }
      curr = nodes[curr].children[idx];
    }
    nodes[curr].is_word = true;
  }
};

class Solution {
  Trie trie;
  int dp[33];
  bool is_concat(const string& s) {
    const int n = s.size();
    memset(dp, 0, sizeof dp);

    for (int i = n - 1; i >= 0; i--) {
      int curr = 0;
      for (int j = i; j < n; j++) {
        const int idx = s[j] - 'a';
        curr = trie.nodes[curr].children[idx];
        if (curr == -1) break;
        if (trie.nodes[curr].is_word && dp[j + 1] != 0) {
          dp[i] = 2;
          break;
        }

        if (trie.nodes[curr].is_word && j == n - 1) {
          dp[i] = 1;
        }
      }
    }

    return dp[0] > 1;
  }

 public:
  vector<string> findAllConcatenatedWordsInADict(const vector<string>& words) {
    for (const string& s : words) trie.insert(s);
    vector<string> ans;
    for (const string& s : words) {
      if (is_concat(s)) ans.emplace_back(s);
    }
    return ans;
  }
};
