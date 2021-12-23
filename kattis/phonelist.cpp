#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
  map<char, shared_ptr<TrieNode>> children;
  bool word_end = false;
};

struct Trie {
  Trie() { root = make_shared<TrieNode>(); }

  int consistent(const string& word) const {
    shared_ptr<TrieNode> curr = root;

    for (char c : word) {
      curr = curr->children[c];
      if (curr->word_end && !curr->children.empty()) return false;
    }

    return true;
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
  shared_ptr<TrieNode> root;
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    Trie trie;
    vector<string> words(N);

    for (int i = 0; i < N; i++) {
      cin >> words[i];
      trie.insert(words[i]);
    }

    bool ok = true;

    for (const string& word : words) {
      if (!trie.consistent(word)) {
        ok = false;
        break;
      }
    }

    cout << (ok ? "YES" : "NO") << endl;
  }
}
