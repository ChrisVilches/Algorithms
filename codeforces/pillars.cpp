#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX = 100'007;
ll pillars[MAX];
pair<ll, int> asc[MAX];
int tree[4 * MAX];
int dp[MAX];
int next_pillar[MAX];
int asc_idx[MAX];

int max_idx(const int a, const int b) {
  if (a == -1 || b == -1) return max(a, b);
  return dp[a] > dp[b] ? a : b;
}

void build_tree(const int p, const int l, const int r) {
  if (l == r) {
    tree[p] = l;
    dp[l] = 0;
  } else {
    build_tree(2 * p, l, (l + r) / 2);
    build_tree(2 * p + 1, (l + r) / 2 + 1, r);
    tree[p] = max_idx(tree[2 * p], tree[2 * p + 1]);
  }
}

int max_query(const int p, const int l, const int r, const int i, const int j) {
  if (i > r || j < l) return -1;
  if (i <= l && r <= j) return tree[p];
  const int m = (l + r) / 2;
  return max_idx(max_query(2 * p, l, m, i, j), max_query(2 * p + 1, m + 1, r, i, j));
}

void update(const int p, const int l, const int r, const int pos, const int val) {
  if (l == r) {
    dp[l] = val;
  } else {
    int m = (l + r) / 2;
    if (pos <= m)
      update(2 * p, l, m, pos, val);
    else
      update(2 * p + 1, m + 1, r, pos, val);

    tree[p] = max_idx(tree[2 * p], tree[2 * p + 1]);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  ll D;

  while (cin >> N >> D) {
    for (int i = 0; i < N; i++) cin >> pillars[i];
    for (int i = 0; i < N; i++) asc[i] = {pillars[i], i};

    sort(asc, asc + N);
    for (int i = 0; i < N; i++) asc_idx[asc[i].second] = i;

    build_tree(1, 0, N - 1);

    for (int i = N - 1; i >= 0; i--) {
      const ll h = pillars[i];

      const int j = upper_bound(asc, asc + N, make_pair(h - D, INT_MAX)) - asc - 1;
      const int k = lower_bound(asc, asc + N, make_pair(h + D, INT_MIN)) - asc;

      const int x = max_query(1, 0, N - 1, 0, j);
      const int y = max_query(1, 0, N - 1, k, N - 1);
      const int next_idx = max_idx(x, y);

      if (next_idx != -1) next_pillar[i] = asc[next_idx].second;

      update(1, 0, N - 1, asc_idx[i], ~next_idx ? 1 + dp[next_idx] : 1);
    }

    const int max_idx = max_query(1, 0, N - 1, 0, N - 1);

    const int path_length = dp[max_idx];

    cout << path_length << endl;

    for (int i = 0, p = asc[max_idx].second; i < path_length; i++) {
      cout << p + 1 << " ";
      p = next_pillar[p];
    }
    cout << endl;
  }
}
