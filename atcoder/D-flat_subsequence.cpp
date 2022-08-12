#include <bits/stdc++.h>
using namespace std;

const int MAX = 300'007;
int A[MAX];
pair<int, int> asc[MAX];
int tree[4 * MAX], asc_idx[MAX];

int max_query(const int p, const int l, const int r, const int i, const int j) {
  if (i > r || j < l) return 0;
  if (i <= l && r <= j) return tree[p];
  const int m = (l + r) / 2;
  return max(max_query(2 * p, l, m, i, j), max_query(2 * p + 1, m + 1, r, i, j));
}

void update(const int p, const int l, const int r, const int pos, const int val) {
  if (l == r) {
    tree[p] = val;
  } else {
    int m = (l + r) / 2;
    if (pos <= m)
      update(2 * p, l, m, pos, val);
    else
      update(2 * p + 1, m + 1, r, pos, val);

    tree[p] = max(tree[2 * p], tree[2 * p + 1]);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, K;

  while (cin >> N >> K) {
    memset(tree, 0, sizeof tree);
    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < N; i++) asc[i] = {A[i], i};

    sort(asc, asc + N);
    for (int i = 0; i < N; i++) asc_idx[asc[i].second] = i;

    for (int i = N - 1; i >= 0; i--) {
      // TODO: Analyze what I did here (lower/upper bound exact usage).
      const int x = lower_bound(asc, asc + N, make_pair(A[i] - K, INT_MIN)) - asc;
      const int y = upper_bound(asc, asc + N, make_pair(A[i] + K, INT_MAX)) - asc - 1;

      const int val = 1 + max_query(1, 0, N - 1, x, y);

      update(1, 0, N - 1, asc_idx[i], val);
    }

    cout << max_query(1, 0, N - 1, 0, N - 1) << endl;
  }
}
