#include <bits/stdc++.h>
using namespace std;

class Trie {
  struct Node {
    unordered_map<char, unique_ptr<Node>> children;
    bool is_end = false;
  };

  unique_ptr<Node> root = make_unique<Node>();

  Node* find(const string& s) const {
    Node* curr = root.get();
    for (const char c : s) {
      if (!curr->children.count(c)) return nullptr;
      curr = curr->children[c].get();
    }
    return curr;
  }

 public:
  void insert(const string& word) {
    Node* curr = root.get();
    for (const char c : word) {
      if (!curr->children.count(c)) {
        curr->children[c] = make_unique<Node>();
      }
      curr = curr->children[c].get();
    }
    curr->is_end = true;
  }

  bool search(const string& word) const {
    Node* n = find(word);
    return n && n->is_end;
  }

  bool startsWith(const string& prefix) const { return find(prefix) != nullptr; }
};
