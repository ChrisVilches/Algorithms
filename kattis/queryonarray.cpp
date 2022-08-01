#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;

ll mod(ll n) { return (n < 0 ? n + MOD : n) % MOD; }
ll mult(const ll a, const ll b) { return mod(mod(a) * mod(b)); }
void add(ll& a, const ll b) { a = mod(mod(a) + mod(b)); }

ll tree[4 * 100007];
ll lazy[4 * 100007][4];
ll psum[100007][4];

ll psum_range_sum(const int c, const int l, const int r) {
  return mod(psum[r + 1][c] - psum[l][c]);
}

void propagate_one_level(int node, int a, int b) {
  if (!lazy[node][0] && !lazy[node][1] && !lazy[node][2] && !lazy[node][3]) return;

  for (int c = 0; c < 4; c++)
    add(tree[node], mult(psum_range_sum(c, a, b), lazy[node][c]));

  if (a != b) {
    for (int c = 0; c < 4; c++) {
      add(lazy[node * 2][c], lazy[node][c]);
      add(lazy[node * 2 + 1][c], lazy[node][c]);
    }
  }

  for (int c = 0; c < 4; c++) lazy[node][c] = 0;
}

void update_tree(int node, int a, int b, int i, int j, array<ll, 4> coefficients) {
  propagate_one_level(node, a, b);

  if (a > b || a > j || b < i) return;

  if (i <= a && b <= j) {
    for (int c = 0; c < 4; c++)
      add(tree[node], mult(psum_range_sum(c, a, b), coefficients[c]));

    if (a != b) {
      for (int c = 0; c < 4; c++) {
        add(lazy[node * 2][c], coefficients[c]);
        add(lazy[node * 2 + 1][c], coefficients[c]);
      }
    }
    return;
  }

  update_tree(node * 2, a, (a + b) / 2, i, j, coefficients);
  update_tree(1 + node * 2, 1 + (a + b) / 2, b, i, j, coefficients);

  tree[node] = mod(tree[node * 2] + tree[node * 2 + 1]);
}

ll range_sum(int node, int a, int b, int i, int j) {
  if (a > j || b < i) return 0;

  propagate_one_level(node, a, b);

  if (i <= a && b <= j) return tree[node];

  const ll q1 = range_sum(node * 2, a, (a + b) / 2, i, j);
  const ll q2 = range_sum(1 + node * 2, 1 + (a + b) / 2, b, i, j);

  return mod(q1 + q2);
}

array<ll, 4> get_coefficients(const ll x, const bool negate = false) {
  array<ll, 4> res{0, 0, 0, negate ? -1 : 1};

  res[0] = (-x * x * x) + (6 * x * x) - (11 * x) + 6;
  res[1] = (3 * x * x) - (12 * x) + 11;
  res[2] = (-3 * x) + 6;

  if (negate) {
    res[0] *= -1;
    res[1] *= -1;
    res[2] *= -1;
  }

  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, Q;

  cin >> N >> Q;

  for (int i = 0; i < N; i++) {
    for (int c = 0; c < 4; c++) {
      psum[0][c] = 0;
      psum[i + 1][c] = mod(psum[i][c] + pow(i, c));
    }
  }

  while (Q--) {
    int type, x, y;
    cin >> type >> x >> y;
    x--;
    y--;

    switch (type) {
      case 0:
        cout << range_sum(1, 0, N - 1, x, y) << '\n';
        break;
      case 1:
        update_tree(1, 0, N - 1, x, y, get_coefficients(x));
        break;
      case 2:
        update_tree(1, 0, N - 1, x, y, get_coefficients(x, true));
        break;
    }
  }
}
