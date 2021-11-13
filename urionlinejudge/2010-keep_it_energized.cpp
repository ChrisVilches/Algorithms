#include <bits/stdc++.h>

using namespace std;

#define MAX 100007

int N, M, E_prefix[MAX], cost[MAX];

struct Shop {
  int level, energy, cost, to;
  void read() {
    cin >> level >> energy >> cost;
    level--;
  }

  void compute_range() {
    int left = level, right = N;
    while (left <= right) {
      int mid = (left + right) / 2;
      if (E_prefix[mid] <= energy + E_prefix[level])
        left = mid + 1;
      else
        right = mid - 1;
    }
    to = right;
  }
} S[MAX];

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

inline bool decreasing(const Shop& s1, const Shop& s2) {
  return s1.level > s2.level;
}

void solve() {
  E_prefix[0] = 0;
  for (int i = 0; i < N; i++) {
    cin >> E_prefix[i + 1];
    E_prefix[i + 1] += E_prefix[i];
  }

  for (int i = 0; i < M; i++) {
    S[i].read();
    S[i].compute_range();
  }

  sort(S, S + M, decreasing);

  fill(cost, cost + N + 1, INT_MAX);
  cost[N] = 0;

  Segtree st(cost, N + 1);

  for (int i = 0; i < M; i++) {
    Shop& shop = S[i];
    int min_val = st.query(shop.level + 1, shop.to);
    if (min_val >= INT_MAX) continue;

    st.update(shop.level, min(cost[shop.level], min_val + shop.cost));
  }

  cout << (cost[0] >= INT_MAX ? -1 : cost[0]) << endl;
}

int main() {
  while (scanf("%d %d", &N, &M) == 2) solve();
}
