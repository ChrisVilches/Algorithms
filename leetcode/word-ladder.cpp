#include <bits/stdc++.h>
using namespace std;

struct Trie {
  void insert(const string& word, const int id) {
    shared_ptr<TrieNode> curr = root;
    for (const char c : word) {
      auto& node = curr->children[c - 'a'];
      if (!node) node = make_shared<TrieNode>();
      curr = node;
    }
    curr->word_end_ids.push_back(id);
  }

  vector<int> find_neighbors(const string& word) {
    if (memo.count(word)) return memo[word];

    vector<int> res;
    shared_ptr<TrieNode> curr = root;

    for (int i = 0; i < (int)word.size(); i++) {
      const auto node = curr->children[word[i] - 'a'];

      for (auto other : curr->children) {
        if (other == node) continue;

        for (int j = i + 1; j < (int)word.size() && other; j++)
          other = other->children[word[j] - 'a'];

        if (other)
          for (const auto x : other->word_end_ids) res.emplace_back(x);
      }

      curr = node;
    }

    return memo[word] = res;
  }

 private:
  struct TrieNode {
    array<shared_ptr<TrieNode>, 26> children;
    vector<int> word_end_ids;
  };

  shared_ptr<TrieNode> root = make_shared<TrieNode>();
  unordered_map<string, vector<int>> memo;
};

class Solution {
 public:
  int ladderLength(string beginWord, string endWord, vector<string>& words) {
    words.emplace_back(beginWord);
    Trie trie;
    for (int i = 0; i < (int)words.size(); i++) {
      trie.insert(words[i], i);
    }

    int to = -1;

    for (int i = 0; i < (int)words.size(); i++) {
      if (words[i] == endWord) {
        to = i;
        break;
      }
    }
    if (to == -1) return 0;

    const int from = words.size() - 1;

    queue<pair<int, int>> q;
    q.emplace(from, 1);
    vector<bool> visited(words.size(), false);

    while (!q.empty()) {
      const auto [u, dist] = q.front();
      q.pop();

      if (u == to) return dist;

      for (const int v : trie.find_neighbors(words[u])) {
        if (visited[v]) continue;
        q.emplace(v, dist + 1);
        visited[v] = u;
      }
    }

    return 0;
  }
};
