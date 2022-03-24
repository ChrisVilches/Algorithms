#include <bits/stdc++.h>
using namespace std;

#define MAX 100001

vector<int> heights;
int N, L[MAX], R[MAX];

template <class T, class TAssociativeFn>
struct SparseTable {
  SparseTable(const T* A, const int N) : K(log2(N)), lookup(N, vector<T>(K + 1)) {
    for (int i = 0; i < N; i++) lookup[i][0] = A[i];

    for (int j = 1; j <= K; j++)
      for (int i = 0; i + (1 << j) <= N; i++)
        lookup[i][j] = fn(lookup[i][j - 1], lookup[i + (1 << (j - 1))][j - 1]);
  }

  T query(int L, int R) const {
    int i = 31 - __builtin_clz(R - L + 1);
    return fn(lookup[L][i], lookup[R - (1 << i) + 1][i]);
  }

  static SparseTable from_vector(const vector<T>& v) {
    return SparseTable<T, TAssociativeFn>(&v[0], v.size());
  }

 private:
  TAssociativeFn fn;
  const int K;
  vector<vector<T>> lookup;
};

template <class T>
struct MinFn {
  T operator()(const T a, const T b) const { return min(a, b); }
};

bool is_peak(int idx) {
  return (heights[idx - 1] < heights[idx]) && (heights[idx] > heights[idx + 1]);
}

bool is_ultra(const SparseTable<int, MinFn<int>>& st, int idx) {
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
  heights.assign(N, 0);
  for (int i = 0; i < N; i++) scanf("%d", &heights[i]);

  populate_left_right();

  auto st = SparseTable<int, MinFn<int>>::from_vector(heights);

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
