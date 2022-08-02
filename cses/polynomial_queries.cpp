#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define MAX_N 200007

ll tree[4 * MAX_N];
ll lazy[4 * MAX_N][2];
ll psum[MAX_N];
ll sequence[MAX_N];

ll psum_range_sum(const int l, const int r) { return psum[r + 1] - psum[l]; }

void propagate_one_level(int node, int a, int b) {
  if (!lazy[node][0] && !lazy[node][1]) return;

  tree[node] += psum_range_sum(a, b) * lazy[node][0];
  tree[node] += (b - a + 1) * lazy[node][1];

  if (a != b) {
    for (int i = 0; i < 2; i++) {
      lazy[node * 2][i] += lazy[node][i];
      lazy[node * 2 + 1][i] += lazy[node][i];
    }
  }

  lazy[node][0] = 0;
  lazy[node][1] = 0;
}

void update_tree(int node, int a, int b, int i, int j) {
  propagate_one_level(node, a, b);
  if (a > j || b < i) return;

  if (i <= a && b <= j) {
    tree[node] += psum_range_sum(a, b);
    tree[node] += (b - a + 1) * (1LL - i);

    if (a != b) {
      lazy[node * 2][0]++;
      lazy[node * 2][1] += (1LL - i);

      lazy[node * 2 + 1][0]++;
      lazy[node * 2 + 1][1] += (1LL - i);
    }
    return;
  }

  update_tree(node * 2, a, (a + b) / 2, i, j);
  update_tree(1 + node * 2, 1 + (a + b) / 2, b, i, j);

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

  iota(psum + 1, psum + N + 1, 0);
  partial_sum(psum, psum + N + 1, psum);

  while (Q--) {
    int type, x, y;
    cin >> type >> x >> y;
    x--;
    y--;

    switch (type) {
      case 1:
        update_tree(1, 0, N - 1, x, y);
        break;
      case 2:
        cout << range_sum(1, 0, N - 1, x, y) << '\n';
        break;
    }
  }
}
