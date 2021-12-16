#include <bits/stdc++.h>

using namespace std;

int n, k;

struct Tree {
  int value = -1;
  Tree() {}
  Tree(int v) : value(v) {}
  unique_ptr<Tree> left, right;

  void insert(int node) {
    if (value <= node) {
      if (right)
        right->insert(node);
      else
        right = make_unique<Tree>(node);
    } else {
      if (left)
        left->insert(node);
      else
        left = make_unique<Tree>(node);
    }
  }

  uint64_t hash(int factor) {
    uint64_t total = 0;

    if (left)
      total += 0x7c2123c * left->hash(factor + 1) * factor;
    else
      total += 0xc343455 * factor;

    if (right)
      total += 0x919113 * right->hash(factor + 2) * factor;
    else
      total += 0x2af4343 * factor;

    return total;
  }
};

void solve() {
  int node;
  unordered_set<uint64_t> trees;
  for (int i = 0; i < n; i++) {
    Tree t;
    cin >> t.value;
    for (int j = 1; j < k; j++) {
      cin >> node;
      t.insert(node);
    }

    trees.emplace(t.hash(1));
  }

  cout << trees.size() << endl;
}

int main() {
  while (scanf("%d %d", &n, &k) == 2) solve();
  return 0;
}
