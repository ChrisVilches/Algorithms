#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

struct Segtree {
  Segtree(int* arr, int n) {
    tree.assign(4 * n, {0, 0});
    build(arr, 1, 0, n - 1);
  }

  pii query(int p, int L, int R, int i, int j) {
    if (i > R || j < L) return {INT_MAX, INT_MIN};
    if (i <= L && R <= j) return tree[p];

    return merge(query(left(p), L, (L + R) / 2, i, j),
                 query(right(p), (L + R) / 2 + 1, R, i, j));
  }

  void update(int p, int L, int R, int pos, int new_val) {
    if (L == R) {
      tree[p] = {new_val, new_val};
    } else {
      int m = (L + R) / 2;
      if (pos <= m)
        update(left(p), L, m, pos, new_val);
      else
        update(right(p), m + 1, R, pos, new_val);

      tree[p] = merge(tree[left(p)], tree[right(p)]);
    }
  }

 private:
  vector<pii> tree;
  inline int left(int p) { return p << 1; }
  inline int right(int p) { return (p << 1) + 1; }

  pii merge(pii p1, pii p2) {
    return {min(p1.first, p2.first), max(p1.second, p2.second)};
  }

  void build(int* A, int p, int L, int R) {
    if (L == R)
      tree[p] = {A[L], A[L]};
    else {
      build(A, left(p), L, (L + R) / 2);
      build(A, right(p), (L + R) / 2 + 1, R);
      tree[p] = merge(tree[left(p)], tree[right(p)]);
    }
  }
};

int N, Q;
int nums[100'001];

void solve() {
  for (int i = 0; i < N; i++) {
    scanf("%d", &nums[i]);
  }

  scanf("%d", &Q);

  Segtree st(nums, N);

  while (Q--) {
    int query_type, a, b;
    scanf("%d %d %d", &query_type, &a, &b);

    if (query_type == 1) {
      st.update(1, 0, N - 1, a - 1, b);
    } else {
      auto [lo, hi] = st.query(1, 0, N - 1, a - 1, b - 1);
      printf("%d\n", hi - lo);
    }
  }
}

int main() {
  while (scanf("%d", &N) == 1) solve();
}
