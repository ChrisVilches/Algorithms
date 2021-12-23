#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
  map<char, shared_ptr<TrieNode>> children;
  bool word_end = false;
};

struct Trie {
  Trie() { root = make_shared<TrieNode>(); }

  int count(const string& word) const {
    shared_ptr<TrieNode> curr = root;

    int sum = 0;

    for (char c : word) {
      curr = curr->children[c];
      if (curr->word_end || curr->children.size() > 1) sum++;
    }

    return sum;
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

  int N;
  while (cin >> N) {
    Trie trie;
    vector<string> words(N);

    for (int i = 0; i < N; i++) {
      cin >> words[i];
      trie.insert(words[i]);
    }

    int ans = 0;

    for (const string& word : words) {
      ans += trie.count(word);
    }

    printf("%.2f\n", ans / (double)N);
  }
}
