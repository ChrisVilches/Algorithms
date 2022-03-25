#include <bits/stdc++.h>
using namespace std;
#define MAX 100007

int N, M, psum[MAX], cost[MAX];

struct Segtree {
 private:
  vector<int> tree;
  int n;
  int* A;
  inline int left(int p) { return p << 1; }
  inline int right(int p) { return (p << 1) + 1; }

  void build(int* arr, int p, int L, int R) {
    if (L == R)
      tree[p] = arr[L];
    else {
      build(arr, left(p), L, (L + R) / 2);
      build(arr, right(p), (L + R) / 2 + 1, R);
      tree[p] = min(tree[left(p)], tree[right(p)]);
    }
  }

  int query(int p, int L, int R, int i, int j) {
    if (i > R || j < L) return INT_MAX;
    if (L >= i && R <= j) return tree[p];
    return min(query(left(p), L, (L + R) / 2, i, j),
               query(right(p), (L + R) / 2 + 1, R, i, j));
  }

  void update(int p, int L, int R, int pos, int new_val) {
    if (L == R) {
      tree[p] = new_val;
      A[pos] = new_val;
    } else {
      int m = (L + R) / 2;
      if (pos <= m)
        update(left(p), L, m, pos, new_val);
      else
        update(right(p), m + 1, R, pos, new_val);
      tree[p] = min(tree[left(p)], tree[right(p)]);
    }
  }

 public:
  Segtree(int* arr, int _n) : n(_n), A(arr) {
    tree.assign(4 * n, 0);
    build(arr, 1, 0, n - 1);
  }

  int query(int i, int j) { return query(1, 0, n - 1, i, j); }
  void update(int pos, int val) { return update(1, 0, n - 1, pos, val); }
};

struct Shop {
  int level, energy, cost, to;

  static Shop from_stdin() {
    Shop s;
    cin >> s.level >> s.energy >> s.cost;
    s.level--;
    s.compute_range();
    return s;
  }

  void compute_range() {
    to = upper_bound(psum, psum + N + 1, energy + psum[level]) - psum - 1;
  }

  inline bool operator<(const Shop& s) { return level < s.level; }
};

void solve() {
  psum[0] = 0;
  for (int i = 0; i < N; i++) {
    cin >> psum[i + 1];
    psum[i + 1] += psum[i];
  }

  vector<Shop> shops(M);

  for (int i = 0; i < M; i++) shops[i] = Shop::from_stdin();

  sort(shops.rbegin(), shops.rend());

  fill(cost, cost + N, INT_MAX);
  cost[N] = 0;

  Segtree st(cost, N + 1);

  for (const Shop& shop : shops) {
    int min_val = st.query(shop.level + 1, shop.to);
    if (min_val == INT_MAX) continue;

    st.update(shop.level, min(cost[shop.level], min_val + shop.cost));
  }

  cout << (cost[0] == INT_MAX ? -1 : cost[0]) << endl;
}

int main() {
  while (scanf("%d %d", &N, &M) == 2) solve();
}
