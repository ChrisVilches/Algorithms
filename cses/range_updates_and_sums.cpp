#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define MAX_N 200007

ll tree[4 * MAX_N];
ll lazy[4 * MAX_N];
bool lazy_set[4 * MAX_N];
ll sequence[MAX_N];

void propagate_one_level(int node, int a, int b) {
  if (lazy[node] == 0) return;

  if (lazy_set[node]) {
    tree[node] = (b - a + 1) * lazy[node];
  } else {
    tree[node] += (b - a + 1) * lazy[node];
  }

  if (a != b) {
    if (lazy_set[node]) {
      lazy[node * 2] = lazy[node];
      lazy[node * 2 + 1] = lazy[node];

      lazy_set[node * 2] = true;
      lazy_set[node * 2 + 1] = true;
    } else {
      lazy[node * 2] += lazy[node];
      lazy[node * 2 + 1] += lazy[node];
    }

    // TODO: I don't understand why this doesn't work.
    //       The same at the "update_tree" method.
    // lazy_set[node * 2] = lazy_set[node];
    // lazy_set[node * 2 + 1] = lazy_set[node];
  }

  lazy[node] = 0;
  lazy_set[node] = false;
}

void update_tree(int node, int a, int b, int i, int j, ll value, bool is_set) {
  propagate_one_level(node, a, b);

  if (a > j || b < i) return;

  if (i <= a && b <= j) {
    if (is_set) {
      tree[node] = (b - a + 1) * value;
    } else {
      tree[node] += (b - a + 1) * value;
    }

    if (a != b) {
      if (is_set) {
        lazy[node * 2] = value;
        lazy[node * 2 + 1] = value;
        lazy_set[node * 2] = true;
        lazy_set[node * 2 + 1] = true;
      } else {
        lazy[node * 2] += value;
        lazy[node * 2 + 1] += value;
      }
    }
    return;
  }

  update_tree(node * 2, a, (a + b) / 2, i, j, value, is_set);
  update_tree(1 + node * 2, 1 + (a + b) / 2, b, i, j, value, is_set);

  tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll range_sum(int node, int a, int b, int i, int j) {
  if (a > j || b < i) return 0;

  propagate_one_level(node, a, b);

  if (i <= a && b <= j) return tree[node];

  const ll q1 = range_sum(node * 2, a, (a + b) / 2, i, j);
  const ll q2 = range_sum(1 + node * 2, 1 + (a + b) / 2, b, i, j);

  return q1 + q2;
}

void initialize_tree(int p, int a, int b) {
  if (a == b)
    tree[p] = sequence[a];
  else {
    initialize_tree(2 * p, a, (a + b) / 2);
    initialize_tree(2 * p + 1, (a + b) / 2 + 1, b);
    tree[p] = tree[2 * p] + tree[2 * p + 1];
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, Q;
  cin >> N >> Q;

  for (int i = 0; i < N; i++) cin >> sequence[i];

  initialize_tree(1, 0, N - 1);

  while (Q--) {
    int type, x, y, value;
    cin >> type >> x >> y;
    x--;
    y--;

    switch (type) {
      case 3:
        cout << range_sum(1, 0, N - 1, x, y) << '\n';
        break;
      default:
        cin >> value;
        update_tree(1, 0, N - 1, x, y, value, type == 2);
    }
  }
}
