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

    for (size_t i = 0; i < word.size(); i++) {
      const auto node = curr->children[word[i] - 'a'];

      for (auto other : curr->children) {
        if (other == node) continue;

        for (size_t j = i + 1; j < word.size() && other; j++)
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

pair<vector<string>, vector<pair<int, int>>> read() {
  string a, b;
  vector<string> words;
  vector<pair<int, int>> queries;

  while (getline(cin, a) && !a.empty()) words.emplace_back(a);
  while (cin >> a >> b) {
    const int i = find(words.begin(), words.end(), a) - words.begin();
    const int j = find(words.begin(), words.end(), b) - words.begin();
    queries.emplace_back(i, j);
  }

  return {words, queries};
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  Trie trie;
  const auto [words, queries] = read();

  for (size_t i = 0; i < words.size(); i++) {
    trie.insert(words[i], i);
  }

  for (const auto& [from, to] : queries) {
    queue<int> q{{from}};
    vector<int> prev(words.size(), -1);

    while (!q.empty()) {
      const int u = q.front();
      q.pop();

      if (u == to) break;

      for (const int v : trie.find_neighbors(words[u])) {
        if (prev[v] != -1) continue;
        q.push(v);
        prev[v] = u;
      }
    }

    const function<void(int)> traverse_print = [&](const int i) {
      if (i != from) traverse_print(prev[i]);
      cout << words[i] << endl;
    };

    if (prev[to] == -1) {
      cout << "No solution." << endl;
    } else {
      traverse_print(to);
    }

    cout << endl;
  }
}
