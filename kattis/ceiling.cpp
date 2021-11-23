#include <bits/stdc++.h>

using namespace std;

int n, k;

struct Tree {
  int value = -1;
  Tree* left = nullptr;
  Tree* right = nullptr;
  ~Tree() {
    if (left) delete (left);
    if (right) delete (right);
  }

  void insert(int node) {
    if (value <= node) {
      if (right) {
        right->insert(node);
      } else {
        right = new Tree();
        right->value = node;
      }
    } else {
      if (left) {
        left->insert(node);
      } else {
        left = new Tree();
        left->value = node;
      }
    }
  }

  long long hash(int factor) {
    long long total = 0;

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
  unordered_set<long long> trees;
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
