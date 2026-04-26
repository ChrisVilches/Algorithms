#include <bits/stdc++.h>
using namespace std;

struct Trie {
  Trie() { root = make_shared<TrieNode>(); }

  bool contains(const string& word) const {
    function<bool(shared_ptr<TrieNode>, int)> dfs = [&](const shared_ptr<TrieNode> node,
                                                        const size_t idx) -> bool {
      if (idx == word.size()) return node->word_end;

      const char c = word[idx];

      if (c == '.') {
        for (const auto& [_, child] : node->children) {
          if (dfs(child, idx + 1)) return true;
        }
        return false;
      } else {
        return node->children.count(c) && dfs(node->children[c], idx + 1);
      }
    };

    return dfs(root, 0);
  }

  void insert(const string& word) {
    shared_ptr<TrieNode> curr = root;
    for (char c : word) {
      if (!curr->children.count(c)) curr->children[c] = make_shared<TrieNode>();
      curr = curr->children[c];
    }
    curr->word_end = true;
  }

 private:
  struct TrieNode {
    map<char, shared_ptr<TrieNode>> children;
    bool word_end = false;
  };

  shared_ptr<TrieNode> root;
};

class WordDictionary {
  Trie trie;

 public:
  void addWord(const string word) { trie.insert(word); }
  bool search(const string word) const { return trie.contains(word); }
};
