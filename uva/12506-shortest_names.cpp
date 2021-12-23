#include <bits/stdc++.h>
using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode {
  int count = 0;

  shared_ptr<TrieNode> get_child(char c) {
    int idx = c - 'a';
    if (!children[idx]) {
      children[idx] = make_shared<TrieNode>();
      children_count++;
    }
    return children[idx];
  }

  bool has_multiple_children() const { return count > 1 || children_count > 1; }

 private:
  int children_count = 0;
  array<shared_ptr<TrieNode>, ALPHABET_SIZE> children;
};

struct Trie {
  Trie() { root = make_shared<TrieNode>(); }

  int count(const string& word) const {
    shared_ptr<TrieNode> curr = root;

    int sum = 0;

    for (char c : word) {
      curr = curr->get_child(c);
      sum++;
      if (!curr->has_multiple_children()) break;
    }

    return sum;
  }

  void insert(const string& word) {
    shared_ptr<TrieNode> curr = root;
    for (char c : word) {
      curr = curr->get_child(c);
      curr->count++;
    }
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

    int ans = 0;

    for (const string& word : words) {
      ans += trie.count(word);
    }

    cout << ans << endl;
  }
}
