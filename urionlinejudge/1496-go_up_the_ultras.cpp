#include <bits/stdc++.h>
using namespace std;

#define MAX 100001

int N, L[MAX], R[MAX], heights[MAX];

// Segment tree, range minimum query, without updates.

struct Segtree {
 private:
  vector<int> tree;
  int n;
  int left(int p) { return p << 1; }
  int right(int p) { return (p << 1) + 1; }

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

 public:
  Segtree(int* arr, int _n) : n(_n) {
    tree.assign(4 * n, 0);
    build(arr, 1, 0, n - 1);
  }

  int query(int i, int j) { return query(1, 0, n - 1, i, j); }
};

bool is_peak(int idx) {
  return (heights[idx - 1] < heights[idx]) && (heights[idx] > heights[idx + 1]);
}

bool is_ultra(Segtree& st, int idx) {
  if (!is_peak(idx)) return false;

  int left = L[idx], right = R[idx];
  int min_height = 0;

  min_height = max(min_height, st.query(left, idx));
  min_height = max(min_height, st.query(idx, right));
  int prominence = heights[idx] - min_height;

  return prominence >= 150000;
}

void populate_left_right() {
  L[0] = 0;
  for (int i = 1; i < N; i++) {
    L[i] = i - 1;
    while (heights[L[i]] <= heights[i] && L[i] > 0) L[i] = L[L[i]];
  }

  R[N - 1] = N - 1;
  for (int i = N - 2; i >= 0; i--) {
    R[i] = i + 1;
    while (heights[R[i]] <= heights[i] && R[i] < N - 1) R[i] = R[R[i]];
  }
}

void solve() {
  for (int i = 0; i < N; i++) scanf("%d", &heights[i]);

  populate_left_right();

  Segtree st(heights, N + 1);

  bool space = false;
  for (int i = 1; i < N - 1; i++) {
    if (is_ultra(st, i)) {
      space ? printf(" %d", i + 1) : printf("%d", i + 1);
      space = true;
    }
  }
  printf("\n");
}

int main() {
  while (scanf("%d", &N) == 1) solve();
}
