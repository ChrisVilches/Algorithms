#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define MAX_N 100007
#define SPARSE_TABLE_SIZE 18

enum Type { NONE = -1, UNDERFLOW = 0, OVERFLOW = 1 };

struct Segtree {
 private:
  int n;
  ll* A;
  vector<pair<ll, ll>> tree;

  void build(int p, int L, int R) {
    if (L == R)
      tree[p] = {A[L], A[L]};
    else {
      build(2 * p, L, (L + R) / 2);
      build(2 * p + 1, (L + R) / 2 + 1, R);
      tree[p].first = max(tree[2 * p].first, tree[2 * p + 1].first);
      tree[p].second = min(tree[2 * p].second, tree[2 * p + 1].second);
    }
  }

  int query_first(int v, int lv, int rv, int l, int r, ll x, bool gt) {
    if (lv > r || rv < l) return INT_MAX;
    if (l <= lv && rv <= r) {
      if (gt && tree[v].first <= x)
        return INT_MAX;
      else if (!gt && tree[v].second >= x)
        return INT_MAX;

      while (lv != rv) {
        int mid = (lv + rv) / 2;
        if ((gt && tree[v * 2].first > x) || (!gt && tree[v * 2].second < x))
          v = v * 2, rv = mid;
        else
          v = v * 2 + 1, lv = mid + 1;
      }
      return lv;
    }

    int mid = (lv + rv) / 2;
    int rs = query_first(v * 2, lv, mid, l, r, x, gt);
    if (rs != INT_MAX) return rs;
    return query_first(v * 2 + 1, mid + 1, rv, l, r, x, gt);
  }

 public:
  Segtree() {}
  Segtree(ll* arr, int _n) : n(_n), A(arr), tree(4 * n) { build(1, 0, n - 1); }
  int query_first(int i, int j, ll x, bool gt) {
    return query_first(1, 0, n - 1, i, j, x, gt);
  }
};

int N, Q;
ll L, U, psum[MAX_N];
Segtree segtree;
pair<int, Type> sparse_table[2][SPARSE_TABLE_SIZE][MAX_N];

ll psum_range_sum(const int l, const int r) { return psum[r + 1] - psum[l]; }

pair<int, Type> first_outside_range(int i, int j, ll X) {
  i++;
  j++;

  const int overflow = segtree.query_first(i, j, U - X + psum[i - 1], true);
  const int underflow = segtree.query_first(i, j, L - X + psum[i - 1], false);

  if (overflow == INT_MAX && underflow == INT_MAX) return {0, NONE};

  const int idx = overflow < underflow ? overflow : underflow;
  const Type type = overflow < underflow ? OVERFLOW : UNDERFLOW;

  return {idx - 1, type};
}

pair<int, Type> find_last_state(pair<int, Type> state, const int E) {
  while (state.first < E) {
    pair<int, Type> next_state{0, NONE};

    for (int k = 0; k < SPARSE_TABLE_SIZE; k++) {
      auto [idx, type] = sparse_table[state.second][k][state.first];
      if (idx > E || type == NONE) break;
      next_state = {idx, type};
    }

    if (next_state.second == NONE) break;
    state = next_state;
  }
  return state;
}

ll query(const int B, const int E, const ll X) {
  auto state = first_outside_range(B, E, X);

  if (state.second == NONE) return X + psum_range_sum(B, E);

  state = find_last_state(state, E);

  return (state.second == OVERFLOW ? U : L) + psum_range_sum(state.first + 1, E);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N >> L >> U;

  psum[0] = 0;
  for (int i = 0; i < N; i++) {
    cin >> psum[i + 1];
    psum[i + 1] += psum[i];
  }

  segtree = Segtree(psum, N + 1);

  memset(sparse_table, NONE, sizeof sparse_table);

  for (int i = 0; i < N; i++) {
    sparse_table[UNDERFLOW][0][i] = first_outside_range(i + 1, N - 1, L);
    sparse_table[OVERFLOW][0][i] = first_outside_range(i + 1, N - 1, U);
  }

  for (int k = 1; k < SPARSE_TABLE_SIZE; k++) {
    for (int t = 0; t < 2; t++) {
      for (int i = 0; i < N; i++) {
        const auto [idx, type] = sparse_table[t][k - 1][i];
        if (type == NONE) break;
        sparse_table[t][k][i] = sparse_table[type][k - 1][idx];
      }
    }
  }

  cin >> Q;

  while (Q--) {
    int B, E, X;
    cin >> B >> E >> X;

    cout << query(B - 1, E - 1, X) << '\n';
  }
}
