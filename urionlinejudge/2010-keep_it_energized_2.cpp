#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX = 100'007;
ll tree[4 * MAX], psum[MAX];

ll min_query(const int p, const int l, const int r, const int i, const int j) {
  if (i > r || j < l) return INT_MAX;
  if (i <= l && r <= j) return tree[p];
  const int m = (l + r) / 2;
  return min(min_query(2 * p, l, m, i, j), min_query(2 * p + 1, m + 1, r, i, j));
}

void update(const int p, const int l, const int r, const int pos, const ll val) {
  if (l == r) {
    tree[p] = val;
  } else {
    int m = (l + r) / 2;
    if (pos <= m)
      update(2 * p, l, m, pos, val);
    else
      update(2 * p + 1, m + 1, r, pos, val);
    tree[p] = min(tree[2 * p], tree[2 * p + 1]);
  }
}

int main() {
  int N, M;
  while (cin >> N >> M) {
    for (int i = 0; i < N; i++) cin >> psum[i + 1];
    partial_sum(psum, psum + N + 1, psum);

    vector<tuple<ll, ll, ll>> shops(M);
    for (auto& s : shops) cin >> get<0>(s) >> get<1>(s) >> get<2>(s);
    for (auto& s : shops) get<0>(s)--;
    sort(shops.rbegin(), shops.rend());

    fill(tree, tree + 4 * MAX, INT_MAX);
    update(1, 0, N, N, 0);

    for (auto [level, energy, cost] : shops) {
      const int to = upper_bound(psum, psum + N + 1, energy + psum[level]) - psum - 1;
      const ll curr_val = min_query(1, 0, N, level, level);
      const ll new_val = min_query(1, 0, N, level + 1, to) + cost;

      update(1, 0, N, level, min(curr_val, new_val));
    }

    const ll ans = min_query(1, 0, N, 0, 0);
    cout << (ans == INT_MAX ? -1 : ans) << endl;
  }
}
