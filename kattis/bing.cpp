#include <bits/stdc++.h>
using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode {
  array<shared_ptr<TrieNode>, ALPHABET_SIZE> children;
  int count = 1;
};

struct Trie {
  Trie() { root = make_shared<TrieNode>(); }

  int count(const string& word) const {
    shared_ptr<TrieNode> curr = root;

    for (char c : word) {
      int idx = c - 'a';
      if (!curr->children[idx]) return 0;
      curr = curr->children[idx];
    }

    return curr->count;
  }

  void insert(const string& word) {
    shared_ptr<TrieNode> curr = root;
    for (char c : word) {
      int idx = c - 'a';
      if (!curr->children[idx])
        curr = curr->children[idx] = make_shared<TrieNode>();
      else {
        curr = curr->children[idx];
        curr->count++;
      }
    }
  }

 private:
  shared_ptr<TrieNode> root;
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  cin >> N;

  string word;
  Trie trie;

  while (N--) {
    cin >> word;
    cout << trie.count(word) << endl;
    trie.insert(word);
  }
}
