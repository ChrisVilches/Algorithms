#include <bits/stdc++.h>
using namespace std;

struct Trie {
  struct Node {
    array<int, 26> children;
    int word_count = 0;
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
    nodes[curr].word_count++;
  }
};

vector<int> compute_z(const string& s) {
  const int n = s.size();
  vector<int> z(n, 0);

  for (int i = 1, l = 0, r = 0; i < n; i++) {
    if (i < r) z[i] = min(r - i, z[i - l]);

    while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;

    if (i + z[i] > r) {
      l = i;
      r = i + z[i];
    }
  }

  return z;
}

class Solution {
 public:
  long long countPrefixSuffixPairs(const vector<string>& words) {
    Trie trie;

    long long ans = 0;

    for (const string& w : words) {
      int curr = 0;
      const vector<int> z = compute_z(w);

      for (size_t i = 0; i < w.size(); i++) {
        curr = trie.nodes[curr].children[w[i] - 'a'];

        if (curr == -1) break;

        const size_t j = w.size() - 1 - i;
        if (j == 0 || j + z[j] == w.size()) {
          ans += trie.nodes[curr].word_count;
        }
      }

      trie.insert(w);
    }

    return ans;
  }
};
