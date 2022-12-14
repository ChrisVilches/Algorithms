#include <bits/stdc++.h>
using namespace std;

// TODO: Study. I don't know what I did.
// Study the whole algorithm of moving "up"s and "down"s across the tree nodes.

// TODO: Create a folder for "DMOJ". Move this problem and POI (?) to that new folder.
//       Do I have another problem solved in DMOJ as well?
//       Note: I've also solved "Seeing the Boundary" and "Artur" (but I prefer SPOJ and
//       Kattis for these ones.)

const int MAX_N = 2'000'007;

struct Node {
  int up;
  int down;

  Node() : up(0), down(INT_MAX) {}

  void inc(int h) {
    up = max(up, h);
    down = max(down, h);
  }

  void dec(int h) {
    up = min(up, h);
    down = min(down, h);
  }

  int height() const { return min(up, down); }
} tree[4 * MAX_N];

void propagate_one_level(int v, int i, int j) {
  if (i == j) return;

  array<int, 2> children{2 * v, 2 * v + 1};

  for (const int c : children) {
    // TODO: This is probably the hardest thing to understand.
    tree[c].down = min(tree[c].down, tree[v].down);
    tree[c].down = max(tree[c].down, tree[v].up);
    tree[c].up = min(tree[c].up, tree[v].down);
    tree[c].up = max(tree[c].up, tree[v].up);
  }

  tree[v] = Node();
}

// TODO: Also understanding the lazy logic is difficult, probably. Study it!!!!

void update(int v, int l, int r, int i, int j, int op, int h) {
  if (j < l || r < i) return;

  if (i <= l && r <= j) {
    if (op == 1) {
      tree[v].inc(h);
    } else {
      tree[v].dec(h);
    }
  } else {
    propagate_one_level(v, l, r);

    const int m = (l + r) / 2;
    update(2 * v, l, m, i, j, op, h);
    update(2 * v + 1, m + 1, r, i, j, op, h);
  }
}

int query(int v, int l, int r, int i) {
  if (i < l || r < i) return -1;
  if (l == r) return tree[v].height();

  propagate_one_level(v, l, r);
  const int m = (l + r) / 2;
  const int h = query(2 * v, l, m, i);
  if (h != -1) return h;
  return query(2 * v + 1, m + 1, r, i);
}

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int res[]) {
  fill(tree, tree + 4 * n, Node());

  for (int i = 0; i < k; i++) {
    update(1, 0, n - 1, left[i], right[i], op[i], height[i]);
  }

  for (int i = 0; i < n; i++) {
    res[i] = query(1, 0, n - 1, i);
  }
}

int main() {
  int op[100];
  int left[100];
  int right[100];
  int height[100];
  int result[100];

  int n, k;
  while (cin >> n >> k) {
    for (int i = 0; i < k; i++) {
      cin >> op[i] >> left[i] >> right[i] >> height[i];
    }
    buildWall(n, k, op, left, right, height, result);
    for (int i = 0; i < n; i++) {
      cout << result[i] << ' ';
    }
    cout << endl;
  }

  return 0;
}
