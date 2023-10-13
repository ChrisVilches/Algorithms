#include <bits/stdc++.h>
using namespace std;

int nums[30'007];
vector<int> tree[4 * 30'007];

void build(const int v, const int l, const int r) {
  copy(nums + l, nums + r + 1, back_inserter(tree[v]));

  if (l == r) return;

  sort(tree[v].begin(), tree[v].end());
  build(2 * v, l, (l + r) / 2);
  build(2 * v + 1, 1 + (l + r) / 2, r);
}

int query(const int v, const int l, const int r, const int i, const int j, const int k) {
  if (i > r || j < l) return 0;

  if (i <= l && r <= j) {
    const auto count = upper_bound(tree[v].begin(), tree[v].end(), k);
    return tree[v].end() - count;
  }

  const int result1 = query(2 * v, l, (l + r) / 2, i, j, k);
  const int result2 = query(2 * v + 1, 1 + (l + r) / 2, r, i, j, k);

  return result1 + result2;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, Q;
  cin >> N;

  for (int i = 0; i < N; i++) cin >> nums[i];

  build(1, 0, N - 1);

  cin >> Q;

  while (Q--) {
    int i, j, k;
    cin >> i >> j >> k;
    cout << query(1, 0, N - 1, i - 1, j - 1, k) << '\n';
  }
}
